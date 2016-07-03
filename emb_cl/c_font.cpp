
#include "c_font.h"
#include <c_sprite.h>
#include <c_shape.h>
#include <c_emdl.h>
#include <c_image.h>

CFont::CFont( const SFontInfo& info ) {

	Emb::CImage * image = new Emb::CImage( info.bmpPath );
	t_size2D_i imageSize = image->GetSize( );

	s_info_texture texInfo;
	texInfo.internalFormat = EMBR_RGBA;
	texInfo.externalFormat = EMBR_RGBA;
	texInfo.interpolation = EMBR_NEAREST;
	texInfo.image = image;

	hTex tex = EmbR::GenTexture( texInfo );

	t_real pw = 1.0 / ( (t_real) imageSize.w + 1 );
	t_real ph = 1.0 / ( (t_real) imageSize.h + 1 );

	_characters = (hEMDL*) calloc( info.cols * info.rows, sizeof( hEMDL ) );

	for( t_uint j = 0; j < info.rows; j++ ) {
		for( t_uint i = 0; i < info.cols; i++ ) {

			CShape subSprite;

			t_real uvx = pw * info.charWidth * i;
			t_real uvy = ph * info.charHeight * j;

			Vertex3 p0, p1, p2, p3;
			p0.location = { 0, 0, 0 };									p0.uv = { uvx, uvy };
			p1.location = { info.charWidth, 0, 0 };						p1.uv = { uvx + pw * info.charWidth , uvy };
			p2.location = { info.charWidth, info.charHeight, 0 };		p2.uv = { uvx + pw * info.charWidth , uvy + ph * info.charHeight };
			p3.location = { 0, info.charHeight, 0 };					p3.uv = { uvx , uvy + ph * info.charHeight };

			subSprite.AddPoint( p0 );
			subSprite.AddPoint( p1 );
			subSprite.AddPoint( p2 );
			subSprite.AddPoint( p3 );

			hEMDL hemdl = EmbR::UploadEMDL( new Emb::CEMDL2D( subSprite ) );
			hemdl.hTex = tex;

			_characters[i + info.cols * j] = hemdl;

		}
	}

	_info = info;

}

void CFont::DrawString( t_real x, t_real y, std::string s, t_real scale ) {

	Transform2D t0;
	t0._position = { x, y };
	t0._scale = { scale, scale };

	EmbR::PushTransform( t0 );
	for( t_uint i = 0; i < s.size( ); i++ ) {
		Transform2D t1;
		t1._position = { i * _info.charWidth, 0 };
		EmbR::PushTransform( t1 );
		EmbR::DrawEMDL( _characters[s[i] - 32] );
		EmbR::PopTransform( );
	}
	EmbR::PopTransform( );

}