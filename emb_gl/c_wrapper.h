#pragma once

#include <Windows.h>
#include <c_defs.h>

namespace Emb {
	class CImage;
	class CEMDL;
}

class CSprite;
class CShader;

typedef t_uint hTex;

struct hEMDL {
	t_uint handle = 0;
	t_uint nVerts = 0;
	t_uint hTex = 0;
	t_color4_r color = { 1.0, 1.0, 1.0, 1.0 };
};

class EmbR {

	public:
	static void Init( void );
	static void CreateDevice( HWND hwnd );
	static void Clear( void );
	static void Swap( void );
	static void ClearTransformStack( void );
	static void PushTransform( Transform2D& transform );
	static void PopTransform( void );
	static void DrawCircle( Vector2 centre, t_real radius );
	static void DrawPoint( Vector2 point );
	static void SetColor( t_real r, t_real g, t_real b, t_real a = 1.0 );
	static hTex GenTexture( Emb::CImage& image );
	static void DeleteTexture( hTex& texHandle );
	static hEMDL UploadEMDL( Emb::CEMDL * emdl );
	static void DrawEMDL( hEMDL emdl );

	private:

	static CShader _shader;
	static HGLRC _context;
	static HDC _device;
	static RECT _renderBounds;

};