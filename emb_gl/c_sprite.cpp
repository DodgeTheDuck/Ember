
#include "c_sprite.h"
#include <c_image.h>
#include <iostream>
#include <GL\glew.h>
#include <c_emdl.h>

CSprite::CSprite( void ) {
	_mode = BLEND_NORM;
}

void CSprite::CreateFromImage( const char * path ) {
	s_info_texture tex;
	tex.internalFormat = EMBR_RGBA;
	tex.externalFormat = EMBR_RGBA;
	tex.interpolation = EMBR_LINEAR;
	tex.image = new Emb::CImage( path );
	_size = tex.image->GetSize( );
	_hEMDL = EmbR::UploadEMDL( new Emb::CEMDL2D( CShapeRect( -((t_real)_size.w / 2), -( (t_real) _size.h / 2), (t_real) _size.w / 2, (t_real) _size.h / 2 ) ) );
	_hEMDL.hTex = EmbR::GenTexture( tex );
	_hEMDL.color = { 1.0, 1.0, 1.0, 1.0 };
}

void CSprite::Draw( void ) {

	if( !glIsTexture( _hEMDL.hTex ) ) std::cout << "BAD TEXTURE HANDLE";

	if( _mode == BLEND_ADD ) 
		glBlendFunc( GL_SRC_ALPHA, GL_ONE );
	else
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	EmbR::PushMatrix( );
	EmbR::Translate( _transform._position + _origin );
	EmbR::Rotate( _transform._angle );
	EmbR::Scale( _transform._scale );
	EmbR::Translate( -_origin / _transform._scale );

	EmbR::DrawEMDL( _hEMDL );
	
	EmbR::PopMatrix( );

	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

}

void CSprite::SetAlpha( t_real alpha ) {
	_hEMDL.color.a = alpha;
}

void CSprite::SetColor( t_real r, t_real g, t_real b, t_real a ) {
	_hEMDL.color = { r, g, b, a };
}

void CSprite::SetColor( t_color4_r c ) {
	_hEMDL.color = c;
}

t_color4_r CSprite::GetColor( void ) {
	return _hEMDL.color;
}

void CSprite::SetBlendMode( EBlendMode mode ) {
	_mode = mode;
}

void CSprite::SetOrigin( Vector2 origin ) {
	_origin = origin;
}

void CSprite::SetOffset( Vector2 offset ) {
	_transform._position = offset;
}
void CSprite::SetScale( Vector2 scale ) {
	_transform._scale = scale;
}

void CSprite::SetAngle( t_real angle ) {
	_transform._angle = angle;
}

bool CSprite::IsImage( void ) {
	return ( _hEMDL.hTex != 0 );
}
