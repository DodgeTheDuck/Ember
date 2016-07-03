#pragma once

#include <c_defs.h>
#include "c_wrapper.h"

namespace Emb {
	class CImage;
}

enum EBlendMode {
	BLEND_NORM,
	BLEND_ADD
};

class CSprite {

	public:
	CSprite( void );
	void CreateFromImage( const char * path );
	void Draw( void );
	void SetColor( t_real r, t_real g, t_real b, t_real a );
	void SetColor( t_color4_r c );
	t_color4_r GetColor( void );
	void SetBlendMode( EBlendMode mode );
	void SetAlpha( t_real a );
	bool IsImage( void );
	void SetOffset( Vector2 offset );
	void SetOrigin( Vector2 origin );
	void SetAngle( t_real angle );
	void SetScale( Vector2 scale );

	private:
	t_size2D_i _size;
	EBlendMode _mode;
	Transform2D _transform;
	Vector2 _origin;
	hEMDL _hEMDL;

};
