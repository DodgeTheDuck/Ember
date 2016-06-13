#pragma once

#include "c_defs.h"
#include "c_shape.h"
#include <memory>

namespace Emb {

	class CEMDL {

		public:

		float * GetVerts( void ) { return _verts; };
		float * GetUVs( void ) { return _uv; }
		float * GetColors( void ) { return _color; }
		t_uint GetVertCount( void ) { return _vertCount; }
		t_uint GetFloatPerVert( void ) { return _floatPerVert; }
		t_uint GetFloatPerUV( void ) { return _floatPerUV; }
		t_uint GetFloatPerColor( void ) { return _floatPerColor; }

		protected:
		float * _verts;
		float * _uv;
		float * _color;
		t_uint _vertCount;
		t_uint _floatPerVert;
		t_uint _floatPerUV;
		t_uint _floatPerColor;

	};

	class CEMDL2D : public CEMDL {

		public:
		CEMDL2D( CShape shape ) {

			std::vector<Vertex3> points = shape.GetPoints( );

			t_uint size = points.size( );

			_verts = (float*) calloc( size * 2, sizeof( float ) );
			_uv = (float*) calloc( size * 2, sizeof( float ) );
			_color = (float*) calloc( size * 4, sizeof( float ) );

			t_uint vertIndex = 0;
			t_uint coordIndex = 0;
			t_uint colorIndex = 0;

			for( t_uint i = 0; i < size; i++ ) {
				_verts[vertIndex++] = points[i].location.x;
				_verts[vertIndex++] = points[i].location.y;
				_uv[coordIndex++] = points[i].uv.x;
				_uv[coordIndex++] = points[i].uv.y;
				_color[colorIndex++] = points[i].color.r;
				_color[colorIndex++] = points[i].color.g;
				_color[colorIndex++] = points[i].color.b;
				_color[colorIndex++] = points[i].color.a;
			}

			_vertCount = size;
			_floatPerVert = 2;
			_floatPerUV = 2;
			_floatPerColor = 4;

		}

	};

}