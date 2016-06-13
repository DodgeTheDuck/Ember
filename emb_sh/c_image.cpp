
#include "c_image.h"
#include "lodepng.h"

namespace Emb {

	CImage::CImage( const char * path ) {
		LoadFromFile( path );
	}

	void CImage::LoadFromFile( const char * path ) {
		t_uint w;
		t_uint h;
		lodepng::decode( _data, w, h, path );
		_size.w = w;
		_size.h = h;
	}

	t_byte * CImage::GetDataPointer( void ) {
		return &_data[0];
	}

	t_size2D_i& CImage::GetSize( void ) {
		return _size;
	}

}