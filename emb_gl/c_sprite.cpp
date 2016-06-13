
#include "c_sprite.h"
#include <c_image.h>
#include <iostream>
#include <GL\glew.h>
#include <c_emdl.h>

void CSprite::CreateFromImage( Emb::CImage& image ) {
	_size = image.GetSize( );
	_hEMDL = EmbR::UploadEMDL( new Emb::CEMDL2D( CShapeRect( -(_size.w / 2), -(_size.h / 2), _size.w / 2, _size.h / 2 ) ) );
	_hEMDL.hTex = EmbR::GenTexture( image );
	_hEMDL.color = { 1.0, 1.0, 1.0, 1.0 };
}

void CSprite::Draw( void ) {

	if( !glIsTexture( _hEMDL.hTex ) ) std::cout << "BAD TEXTURE HANDLE";

	if( _mode == BLEND_ADD ) 
		glBlendFunc( GL_SRC_ALPHA, GL_ONE );
	else
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	EmbR::DrawEMDL( _hEMDL );

}

void CSprite::SetAlpha( t_real alpha ) {
	_hEMDL.color.a = alpha;
}

void CSprite::SetColor( t_real r, t_real g, t_real b, t_real a ) {
	_hEMDL.color = { r, g, b, a };
}

void CSprite::SetBlendMode( EBlendMode mode ) {
	_mode = mode;
}

bool CSprite::IsImage( void ) {
	return ( _hEMDL.hTex != 0 );
}
