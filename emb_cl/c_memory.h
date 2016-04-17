#pragma once

#include "c_defs.h"
#include "c_singleton.h"

#ifdef _DEBUG
#define TRASH_POOLS 0
#else
#define TRASH_POOLS 0
#endif

namespace EmbCL {

	class CMemChunk {

		public:
		CMemChunk( t_size dataSize ) :
			m_next( NULL ),
			m_prev( NULL ),
			m_dataSize( dataSize ),
			m_free( true ) { };

		void Write( void * dest ) {
			memcpy( dest, this, sizeof( CMemChunk ) );
		}

		void Read( void * src ) {
			memcpy( this, src, sizeof( CMemChunk ) );
		}

		CMemChunk * m_next;
		CMemChunk * m_prev;
		t_size		m_dataSize;
		bool		m_free;

	};

	class CMemPool {

		public:

		inline virtual void *			Allocate( t_size size ) = 0;
		inline virtual void				Free( void * ptr ) = 0;

		inline t_size					GetFreePoolSize( ) const { return m_freePoolSize; }
		inline t_size					GetTotalPoolSize( ) const { return m_totalPoolSize; }

		static const t_byte s_boundsCheckSize = sizeof( void * ) * 2 + sizeof( t_uint ) + sizeof( bool ) + 11;
		static const t_uint s_minFreeBlockSize = 0;

		protected:
		CMemPool( ) :
			m_totalPoolSize( 0 ),
			m_freePoolSize( 0 ) { };
		virtual ~CMemPool( ) { };

		t_size m_totalPoolSize;
		t_size m_freePoolSize;

		unsigned char * m_poolMemory;

	};

	template<typename T>
	class CStackDY : public CMemPool {

		public:
		CStackDY( void );
		~CStackDY( void );

		inline virtual void *	Allocate( t_size size );

		inline virtual void		Free( void * ptr );
		inline void				Push( const T& type );
		inline void				Pop( void );

		T&						Top( void );

		private:

		T& operator[]( int index ) { return (T&) m_poolMemory[index * sizeof( T )]; };

		t_uint _count;

	};

	template<typename T>
	CStackDY<T>::CStackDY( void ) { }

	template<typename T>
	void * CStackDY<T>::Allocate( t_size size ) {
		if( _count > 0 ) {
			if( _count >= m_totalPoolSize / sizeof( T ) ) {
				m_totalPoolSize *= 2;
				m_poolMemory = (unsigned char *) realloc( m_poolMemory, m_totalPoolSize );
			} 
		} else {
			m_poolMemory = (unsigned char *) calloc( size, sizeof( T ) );
			m_totalPoolSize = sizeof( T );
		}
		return &m_poolMemory[_count++ * sizeof( T )];
	}

	template<typename T>
	void CStackDY<T>::Push( const T& type ) {
		memmove( Allocate( 1 ), (void*) &type, sizeof( T ) );
	}

	template<typename T>
	void CStackDY<T>::Pop( void ) {
		m_poolMemory = (unsigned char *) realloc( m_poolMemory, m_totalPoolSize - sizeof( T ) );
		m_totalPoolSize -= sizeof( T );
		_count--;
	}

	template<typename T>
	T& CStackDY<T>::Top( void ) {
		return ( *this )[_count - 1];
	}

	template<typename T>
	void CStackDY<T>::Free( void * ptr ) {

	}

	template<typename T>
	CStackDY<T>::~CStackDY( void ) { }

}