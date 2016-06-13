#pragma once

#include "c_defs.h"
#include "c_std_wrapper.h"

namespace Emb {

	class CImage {

		public:
		EMB_SH_API CImage( const char * path );
		EMB_SH_API void LoadFromFile( const char * path );
		EMB_SH_API t_byte * GetDataPointer( void );
		EMB_SH_API t_size2D_i& GetSize( void );

		private:
		std::vector<unsigned char>	_data;
		t_size2D_i					_size;

	};

}