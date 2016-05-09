#pragma once

#include "c_defs.h"
#include <vector>
#include <stack>

namespace EmbCL {

	template<typename T> class EMB_SH_API CStack : private std::stack<T> {

		public:
		void Push( const T& t ) {
			push( t );
		}

		void Pop( void ) {
			pop( );
		}

		T& Top( void ) {
			return top( );
		}

		t_uint Count( void ) {
			return size( );
		}

	};

	template<typename T> class EMB_SH_API CArray : public std::vector<T> {

		public:

		CArray( void ) {
			_end = false;
			_index = 0;
		}

		void Push( T& t ) {
			push_back( t );
		}

		void Pop( void ) {
			pop_back( );
		}

		t_uint Count( void ) {
			return size( );
		}

		bool End( void ) {
			if( _index >= Count( ) ) {
				_index = 0;
				return true;
			}
			return false;
		}

		T& Iterate( void ) {
			return ( T& ) this[_index++];
		}

		/*inline T& operator[]( int index ) {
			//if( Count( ) == 0 ) MessageBox( NULL, STRING( "EmbCL::CArray OUT OF BOUNDS AT INDEX " ) + STRING( index ), NULL, NULL );
			return (T&) this[index];
		}*/

		private:
		bool _end;
		t_uint _index;

	};

}