#pragma once

#include "c_common.h"

#define EMBER_ENTRY( state, window )																		\
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPSTR lpccmdline, int nCmdShow ) {	\
	EMB::hInstance = hInstance;																				\
	SCore::GetInstance( ).StateManager( ).push( state );													\
	SCore::GetInstance( ).WindowManager( ).push_back( window );												\
	SCore::GetInstance( ).WindowManager( )[0]->Show( );														\
	SCore::GetInstance( ).Init( );																			\
	SCore::GetInstance( ).Run( );																			\
	SCore::GetInstance( ).Shutdown( );																		\
	return 0;																								\
}																											\

using namespace Emb;

namespace EmbCL {

	class CWindow;

	class SCore {

		public:

		SCore( void );
		void Init( void );
		void Run( void );
		void Shutdown( void );

		EMB_CL_API std::stack<CState*>& StateManager( void );
		EMB_CL_API std::vector<CWindow*>& WindowManager( void );

		static SCore& GetInstance( );

		private:

		void _Tick( void );
		void _Draw( void );

		std::stack<CState*>		_states;
		std::vector<CWindow*>	_windows;
		CStopwatch				_frameTimer;

		t_real				_frameDeltaAccumulator;
		t_int32				_frameCount;
		t_real				_secondCounter;

		public:
		SCore( const SCore& ) = delete;
		void operator=( const SCore& ) = delete;

	};

}

