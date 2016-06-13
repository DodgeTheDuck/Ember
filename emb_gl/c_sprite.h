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

	void CreateFromImage( Emb::CImage& image );
	void Draw( void );
	void SetColor( t_real r, t_real g, t_real b, t_real a );
	void SetBlendMode( EBlendMode mode );
	void SetAlpha( t_real a );
	bool IsImage( void );

	private:
	t_size2D_i _size;
	EBlendMode _mode = BLEND_NORM;
	hEMDL _hEMDL;

};
