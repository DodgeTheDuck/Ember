#pragma once

#include "c_common.h"

class hEMDL;
class CSprite;

struct SFontInfo {
	const char * bmpPath;
	t_uint cols;
	t_uint rows;
	t_real charWidth;
	t_real charHeight;
};

class CFont {

	public:
	CFont( const SFontInfo& info );
	void DrawString( t_real x, t_real y, std::string s );

	private:
	SFontInfo _info;
	hEMDL * _characters;

};