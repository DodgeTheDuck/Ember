
#include <iostream>
#include "c_wrapper.h"
#include <GL\glew.h>
#include <c_image.h>
#include "c_sprite.h"
#include <c_emdl.h>
#include "c_shader.h"

HDC				EmbR::_device = 0;
HGLRC			EmbR::_context = 0;
RECT			EmbR::_renderBounds;
CShader			EmbR::_scene;
CShader			EmbR::_post;
CShader			EmbR::_blur;
hFramebuffer	EmbR::_backbuffer;
hFramebuffer	EmbR::_blurbuffer[2];

void setVSync( bool sync ) {
	typedef BOOL( APIENTRY *PFNWGLSWAPINTERVALPROC )( int );
	PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT = 0;
	const char *extensions = (char*) glGetString( GL_EXTENSIONS );
	if( strstr( extensions, "WGL_EXT_swap_control" ) == 0 ) {
		return;
	} else {
		wglSwapIntervalEXT = (PFNWGLSWAPINTERVALPROC) wglGetProcAddress( "wglSwapIntervalEXT" );

		if( wglSwapIntervalEXT )
			wglSwapIntervalEXT( sync );
	}
}

void EmbR::Init( void ) {

	if( !_device ) return;

	wglMakeCurrent( _device, _context );

	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	glShadeModel( GL_SMOOTH );
	glClearColor( 0, 0, 0, 0 );
	glClearDepth( 1.0 );
	glDepthFunc( GL_LEQUAL );

	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	glewInit( );

	glMatrixMode( GL_PROJECTION );
	glOrtho( 0, _renderBounds.right - _renderBounds.left, _renderBounds.bottom - _renderBounds.top, 0, -1.0, 1.0 );
	glViewport( 0, 0, WINDOW_W, WINDOW_H );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	setVSync( 0 );

	glPointSize( 4 );

	_scene.LoadFromFile( "RESOURCE/shader/frag.glsl", CShader::SHADER_FRAGMENT );
	_scene.LoadFromFile( "RESOURCE/shader/vert.glsl", CShader::SHADER_VERTEX );
	_scene.Link( );

	_post.LoadFromFile( "RESOURCE/shader/fragPOST.glsl", CShader::SHADER_FRAGMENT );
	_post.LoadFromFile( "RESOURCE/shader/vertPOST.glsl", CShader::SHADER_VERTEX );
	_post.Link( );

	_blur.LoadFromFile( "RESOURCE/shader/fragBLUR.glsl", CShader::SHADER_FRAGMENT );
	_blur.LoadFromFile( "RESOURCE/shader/vertBLUR.glsl", CShader::SHADER_VERTEX );
	_blur.Link( );


	_post.Enable( );
	float windowSize[2] = { WINDOW_W, WINDOW_H };
	_post.UniformVec2( "s_screen.window_size", windowSize );
	_post.UniformVec2( "s_screen.view_size", windowSize );
	_post.Disable( );

	s_info_framebuffer backbufferInfo;

	backbufferInfo.colorBufferCount = 2;
	backbufferInfo.useHDR =  true;
	backbufferInfo.width = WINDOW_W;
	backbufferInfo.height = WINDOW_H;
	backbufferInfo.attachments = ( EMBR_FBO_COLOR | EMBR_FBO_DEPTH | EMBR_FBO_STENCIL );

	_backbuffer = GenFramebuffer( backbufferInfo );

	s_info_framebuffer blurbufferInfo;

	blurbufferInfo.colorBufferCount = 1;
	blurbufferInfo.useHDR = true;
	blurbufferInfo.width = WINDOW_W;
	blurbufferInfo.height = WINDOW_H;
	blurbufferInfo.attachments |= EMBR_FBO_COLOR;

	_blurbuffer[0] = GenFramebuffer( blurbufferInfo );
	_blurbuffer[1] = GenFramebuffer( blurbufferInfo );

}

void EmbR::CreateDevice( HWND hwnd ) {
	GetWindowRect( hwnd, &_renderBounds );
	_device = GetDC( hwnd );
	_context = wglCreateContext( _device );
	if( !_context ) {
		ErrorExit( "CreateDevice" );
	}
}

void EmbR::Clear( void ) {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void EmbR::Swap( void ) {
	SwapBuffers( _device );
}

void EmbR::PushTransform( Transform2D& transform ) {
	glPushMatrix( );
	glTranslatef( transform._position.x, transform._position.y, 0 );
	glRotatef( transform._angle, 0, 0, 1 );
	glScalef( transform._scale.x, transform._scale.y, 1.0 );
}

void EmbR::PopTransform( void ) {
	glPopMatrix( );
}

void EmbR::ClearTransformStack( void ) {
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
}

void EmbR::DrawCircle( Vector2 centre, t_real radius ) {

	t_real res = radius * 2;

	glColor3f( 1.0, 1.0, 1.0 );

	glBegin( GL_LINES );
	for( t_uint i = 0; i < res; i++ ) {

		t_real angle0 = i * ( ( PI * 2 ) / res );
		t_real angle1 = ( i + 1 ) * ( ( PI * 2 ) / res );

		glVertex2f(
			centre.x + cos( angle0 ) * radius,
			centre.y + sin( angle0 ) * radius
		);

		glVertex2f(
			centre.x + cos( angle1 ) * radius,
			centre.y + sin( angle1 ) * radius
		);

	}
	glEnd( );

}

void EmbR::DrawPoint( Vector2 point ) {
	glBegin( GL_POINTS );
	glVertex2f( point.x, point.y );
	glEnd( );
}

void EmbR::SetColor( t_real r, t_real g, t_real b, t_real a ) {
	glColor4f( r, g, b, a );
}

hTex EmbR::GenTexture( s_info_texture& info ) {
	
	t_byte * data = NULL;

	if( info.image ) {
		t_size2D_i size = info.image->GetSize( );
		info.width = size.w;
		info.height = size.h;
		data = info.image->GetDataPointer( );
	}

	GLuint tex = 0;

	glGenTextures( 1, &tex );
	glBindTexture( GL_TEXTURE_2D, tex );

	glTexImage2D( GL_TEXTURE_2D, 0, info.internalFormat, info.width, info.height, 0, info.externalFormat, GL_UNSIGNED_BYTE, data );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, info.interpolation );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, info.interpolation );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	glBindTexture( GL_TEXTURE_2D, 0 );

	return tex;

}

void EmbR::DeleteTexture( hTex& texHandle ) {
	glDeleteTextures( 1, &texHandle );
}

hEMDL EmbR::UploadEMDL( Emb::CEMDL * emdl ) {

	GLuint vao;
	GLuint vbo[3];

	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );
	glGenBuffers( 3, vbo );

	glBindBuffer( GL_ARRAY_BUFFER, vbo[0] );
	glBufferData( GL_ARRAY_BUFFER, emdl->GetVertCount( ) * emdl->GetFloatPerVert( ) * sizeof( float ), &emdl->GetVerts( )[0], GL_DYNAMIC_DRAW );
	glVertexAttribPointer( 0, emdl->GetFloatPerVert( ), GL_FLOAT, GL_FALSE, 0, 0 );
	glEnableVertexAttribArray( 0 );

	glBindBuffer( GL_ARRAY_BUFFER, vbo[1] );
	glBufferData( GL_ARRAY_BUFFER, emdl->GetVertCount( ) * emdl->GetFloatPerUV( ) * sizeof( float ), &emdl->GetUVs( )[0], GL_DYNAMIC_DRAW );
	glVertexAttribPointer( 1, emdl->GetFloatPerUV( ), GL_FLOAT, GL_FALSE, 0, 0 );
	glEnableVertexAttribArray( 1 );

	glBindBuffer( GL_ARRAY_BUFFER, vbo[2] );
	glBufferData( GL_ARRAY_BUFFER, emdl->GetVertCount( ) * emdl->GetFloatPerColor( ) * sizeof( float ), &emdl->GetColors( )[0], GL_DYNAMIC_DRAW );
	glVertexAttribPointer( 2, emdl->GetFloatPerColor( ), GL_FLOAT, GL_FALSE, 0, 0 );
	glEnableVertexAttribArray( 2 );

	hEMDL hemdl;
	hemdl.handle = vao;
	hemdl.nVerts = emdl->GetVertCount( );

	return hemdl;

}

void EmbR::PushMatrix( void ) {
	glPushMatrix( );
}

void EmbR::PopMatrix( void ) {
	glPopMatrix( );
}

void EmbR::Translate( Vector2 translation ) {
	glTranslatef( translation.x, translation.y, 0 );
}

void EmbR::Rotate( t_real angle ) {
	glRotatef( angle, 0, 0, 1 );
}

void EmbR::Scale( Vector2 scale ) {
	glScalef( scale.x, scale.y, 1.0 );
}

void EmbR::DrawEMDL( hEMDL emdl ) {

	_scene.Enable( );
	_scene.UniformVec4( "col", emdl.color );
	glEnableVertexArrayAttrib( emdl.handle, 0 );
	glEnableVertexArrayAttrib( emdl.handle, 1 );
	glEnableVertexArrayAttrib( emdl.handle, 2 );

	glBindTexture( GL_TEXTURE_2D, emdl.hTex );

	glBindVertexArray( emdl.handle );


	glDrawArrays( GL_QUADS, 0, emdl.nVerts );

	glDisableVertexArrayAttrib( emdl.handle, 0 );
	glDisableVertexArrayAttrib( emdl.handle, 1 );
	glDisableVertexArrayAttrib( emdl.handle, 2 );


	_scene.Disable( );


}

hFramebuffer EmbR::GenFramebuffer( s_info_framebuffer& info ) {

	hFramebuffer buffer;

	glGenFramebuffers( 1, &buffer.renderbuffers[EMBR_RBUFF_HANDLE] );
	glBindFramebuffer( GL_FRAMEBUFFER, buffer.renderbuffers[EMBR_RBUFF_HANDLE] );

	if( info.attachments & EMBR_FBO_COLOR ) {

		buffer.frameTextures = (hTex*) calloc( info.colorBufferCount, sizeof( hTex ) );

		for( t_uint i = 0; i < info.colorBufferCount; i++ ) {
			s_info_texture tex;
			tex.width = info.width;
			tex.height = info.height;
			( info.useHDR ) ? tex.internalFormat = EMBR_RGBF : tex.internalFormat = EMBR_RGB;
			tex.interpolation = EMBR_NEAREST;
			tex.image = NULL;
			tex.externalFormat = GL_RGB;
			buffer.frameTextures[i] = GenTexture( tex );
			glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, buffer.frameTextures[i], 0 );
		}

		GLenum * drawBuffers = (GLenum*) calloc( info.colorBufferCount, sizeof( GLenum ) );

		for( t_uint i = 0; i < info.colorBufferCount; i++ ) {
			drawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
		}

		glDrawBuffers( info.colorBufferCount, drawBuffers );

		CShapeRect rect = CShapeRect( 0, 0, info.width, info.height );
		buffer.frameEMDL = UploadEMDL( new Emb::CEMDL2D( rect ) );
		buffer.frameEMDL.hTex = buffer.frameTextures[0];

	} else {
		glFramebufferParameteri( GL_DRAW_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_WIDTH, info.width );
		glFramebufferParameteri( GL_DRAW_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_HEIGHT, info.height );
		glFramebufferParameteri( GL_DRAW_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_SAMPLES, 4 );
	}

	if( ( info.attachments & ( EMBR_FBO_DEPTH | EMBR_FBO_STENCIL ) == ( EMBR_FBO_DEPTH | EMBR_FBO_STENCIL ) ) ) {
		glGenRenderbuffers( 1, &buffer.renderbuffers[EMBR_RBUFF_DEPTH] );
		glBindRenderbuffer( GL_RENDERBUFFER, buffer.renderbuffers[EMBR_RBUFF_DEPTH] );
		glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, info.width, info.height );
		glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, buffer.renderbuffers[EMBR_RBUFF_DEPTH] );
	} else if( info.attachments & EMBR_FBO_DEPTH ) {
		glGenRenderbuffers( 1, &buffer.renderbuffers[EMBR_RBUFF_DEPTH] );
		glBindRenderbuffer( GL_RENDERBUFFER, buffer.renderbuffers[EMBR_RBUFF_DEPTH] );
		glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT, info.width, info.height );
		glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, buffer.renderbuffers[EMBR_RBUFF_DEPTH] );
	}


	if( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE ) {
		std::cout << "FRAMEBUFFER FAILED";
	}

	return buffer;

}

void EmbR::SetRenderTarget( hFramebuffer& buffer ) {
	glBindFramebuffer( GL_FRAMEBUFFER, buffer.renderbuffers[EMBR_RBUFF_HANDLE] );
}

void EmbR::BeginFrame( void ) {
	SetRenderTarget( _backbuffer );
	Clear( );
}

void EmbR::EndFrame( void ) {

	ClearTransformStack( );

	glReadBuffer( GL_COLOR_ATTACHMENT0 );

	int amount = 10;

	_blur.Enable( );

	for( t_uint i = 0; i < amount; i++ ) {

		int index = i % 2;

		glBindFramebuffer( GL_FRAMEBUFFER, _blurbuffer[index].renderbuffers[0] );
		_blur.UniformInt( "horizontal", index );
		glBindTexture( GL_TEXTURE_2D, ( i == 0 ) ? _backbuffer.frameTextures[1] : _blurbuffer[!index].frameTextures[0] );
		GLuint blurHandle = _blurbuffer[!index].frameEMDL.handle;
		glEnableVertexArrayAttrib( blurHandle, 0 );
		glEnableVertexArrayAttrib( blurHandle, 1 );
		glEnableVertexArrayAttrib( blurHandle, 2 );
		glBindVertexArray( blurHandle );
		glDrawArrays( GL_QUADS, 0, _blurbuffer[!index].frameEMDL.nVerts );
		glDisableVertexArrayAttrib( blurHandle, 0 );
		glDisableVertexArrayAttrib( blurHandle, 1 );
		glDisableVertexArrayAttrib( blurHandle, 2 );
		

	}

	_blur.Disable( );

	glBindFramebuffer( GL_FRAMEBUFFER, 0 );

	GLuint handle = _backbuffer.frameEMDL.handle;

	glEnableVertexArrayAttrib( handle, 0 );
	glEnableVertexArrayAttrib( handle, 1 );
	glEnableVertexArrayAttrib( handle, 2 );

	glBindVertexArray( handle );

	_post.Enable( );
	_post.UniformVec4( "col", { 1.0, 1.0, 1.0, 1.0 } );
	_post.UniformInt( "scene", 0 );
	_post.UniformInt( "blur", 1 );

	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, _backbuffer.frameTextures[0] );
	glActiveTexture( GL_TEXTURE1 );
	glBindTexture( GL_TEXTURE_2D, _blurbuffer[0].frameTextures[0] );

	glDrawArrays( GL_QUADS, 0, _backbuffer.frameEMDL.nVerts );

	_post.Disable( );

	glDisableVertexArrayAttrib( handle, 0 );
	glDisableVertexArrayAttrib( handle, 1 );
	glDisableVertexArrayAttrib( handle, 2 );
	glActiveTexture( GL_TEXTURE0 );
	Swap( );

}

CShader& EmbR::GetPostShader( void ) {
	return _post;
}