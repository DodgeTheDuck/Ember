#pragma once

#include "c_common.h"

#define EMBER_ENTRY( state )																		\
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPSTR lpccmdline, int nCmdShow ) {	\
	EMB::hInstance = hInstance;																				\
	S_Core::GetInstance( ).StateManager( ).Push( state );													\
	S_Core::GetInstance( ).Init( );																			\
	S_Core::GetInstance( ).Run( );																			\
	S_Core::GetInstance( ).Shutdown( );																		\
	return 0;																								\
}																											\

namespace EmbCL {

	class CWindow;

	class S_Core {

		public:

		S_Core( void );
		void Init( void );
		void Run( void );
		void Shutdown( void );

		EMB_CL_API CStack<IState*>& StateManager( void );
		EMB_CL_API CArray<CWindow*>& WindowManager( void );

		static S_Core& GetInstance( );

		private:

		void _Tick( void );
		void _Draw( void );

		CStack<IState*> _states;
		CArray<CWindow*> _windows;

		public:
		S_Core( const S_Core& ) = delete;
		void operator=( const S_Core& ) = delete;

	};

}

