#pragma once

#include <Windows.h>
#include <c_defs.h>

#define EMBR_RGB		0x1907
#define EMBR_RGBA		0x1908
#define EMBR_RGBF		0x881B

#define EMBR_LINEAR		0x2601
#define EMBR_NEAREST	0x2600

#define EMBR_FBO_COLOR		0x01
#define EMBR_FBO_DEPTH		0x02
#define EMBR_FBO_STENCIL	0x04

namespace Emb {
	class CImage;
	class CEMDL;
}

class CSprite;
class CShader;

typedef t_uint hTex;
typedef t_uint hBuf;

enum {
	EMBR_RBUFF_HANDLE,
	EMBR_RBUFF_DEPTH
};

struct hEMDL {
	t_uint handle = 0;
	t_uint nVerts = 0;
	t_uint hTex = 0;
	t_color4_r color = { 1.0, 1.0, 1.0, 1.0 };
};

struct hFramebuffer {
	t_uint renderbuffers[3];
	t_uint * frameTextures;
	hEMDL  frameEMDL;
};

struct s_info_texture {
	t_uint internalFormat;
	t_uint externalFormat;
	t_uint interpolation;
	t_size width = 0;
	t_size height = 0;
	Emb::CImage * image = NULL;
};

struct s_info_framebuffer {
	t_size width;
	t_size height;
	t_uint colorBufferCount;
	t_ubyte attachments;
	bool useHDR;
};

class EmbR {

	public:
	static void Init( void );
	static void CreateDevice( HWND hwnd );
	static void Clear( void );
	static void Swap( void );
	static void ClearTransformStack( void );
	static void PushTransform( Transform2D& transform );
	static void PushMatrix( void );
	static void PopMatrix( void );
	static void PopTransform( void );
	static void DrawCircle( Vector2 centre, t_real radius );
	static void DrawPoint( Vector2 point );
	static void SetColor( t_real r, t_real g, t_real b, t_real a = 1.0 );
	static hTex GenTexture( s_info_texture& info );
	static void DeleteTexture( hTex& texHandle );
	static hEMDL UploadEMDL( Emb::CEMDL * emdl );
	static void DrawEMDL( hEMDL emdl );
	static void Translate( Vector2 translation );
	static void Rotate( t_real angle );
	static void Scale( Vector2 scale );
	static void SetRenderTarget( hFramebuffer& framebuffer );
	static void BeginFrame( void );
	static void EndFrame( void );
	static CShader& GetPostShader( void );
	static hFramebuffer GenFramebuffer( s_info_framebuffer& info );

	private:
	static hFramebuffer _backbuffer;
	static hFramebuffer _blurbuffer[2];
	static CShader _scene;
	static CShader _blur;
	static CShader _post;
	static HGLRC _context;
	static HDC _device;
	static RECT _renderBounds;

};