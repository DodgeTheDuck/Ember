
#include <iostream>
#include "c_wrapper.h"
#include <GL\glew.h>
#include <c_image.h>
#include "c_sprite.h"
#include <c_emdl.h>
#include "c_shader.h"

HDC		EmbR::_device = 0;
HGLRC	EmbR::_context = 0;
RECT	EmbR::_renderBounds;
CShader EmbR::_shader;

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
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );

	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	glewInit( );

	glMatrixMode( GL_PROJECTION );
	glOrtho( 0, _renderBounds.right-_renderBounds.left, _renderBounds.bottom-_renderBounds.top, 0, -1.0, 1.0 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	setVSync( 0 );

	glPointSize( 4 );

	_shader.LoadFromFile( "RESOURCE/shader/frag.glsl", CShader::SHADER_FRAGMENT );
	_shader.LoadFromFile( "RESOURCE/shader/vert.glsl", CShader::SHADER_VERTEX );
	_shader.Link( );

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
	glScalef( transform._scale, transform._scale, 1.0 );
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
		t_real angle1 = (i+1) * ( ( PI * 2 ) / res );

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

hTex EmbR::GenTexture( Emb::CImage& image ) {

	GLuint tex = 0;
	t_size2D_i size = image.GetSize( );

	glGenTextures( 1, &tex );
	glBindTexture( GL_TEXTURE_2D, tex );

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, size.w, size.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.GetDataPointer( ) );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
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

void EmbR::DrawEMDL( hEMDL emdl ) {

	_shader.Enable( );

	_shader.UniformVec4( "col", emdl.color );

	glEnableVertexArrayAttrib( emdl.handle, 0 );
	glEnableVertexArrayAttrib( emdl.handle, 1 );
	glEnableVertexArrayAttrib( emdl.handle, 2 );

	glBindTexture( GL_TEXTURE_2D, emdl.hTex );

	glBindVertexArray( emdl.handle );
	glDrawArrays( GL_QUADS, 0, emdl.nVerts );

	glDisableVertexArrayAttrib( emdl.handle, 0 );
	glDisableVertexArrayAttrib( emdl.handle, 1 );
	glDisableVertexArrayAttrib( emdl.handle, 2 );

	_shader.Disable( );

}