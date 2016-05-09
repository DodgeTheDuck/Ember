
#include "c_core.h"
#include "c_state.h"
#include "c_window.h"
#include <c_wrapper.h>

namespace EmbCL {

	S_Core::S_Core( void ) { }

	void S_Core::Init( void ) {
		CWindow * window = new CWindow( { 128, 128, 1024, 1024 }, "Ember Engine", "0" );
		_windows.Push( window );
		_windows[0]->Show( );
		EmbR::Init( _windows[0]->GetHandle( ) );
	}

	void S_Core::Run( void ) {

		while( true ) {

			_Tick( );
			_Draw( );

			MSG msg;

			if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) {
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}

			//_windows[0]->Update( );

		}

	}

	void S_Core::Shutdown( void ) {

	}

	void S_Core::_Tick( void ) {
		_states.Top( )->Tick( );
	}

	void S_Core::_Draw( void ) {
		EmbR::Clear( );
		_states.Top( )->Draw( );
		EmbR::Swap( );
	}

	CStack<IState*>& S_Core::StateManager( void ) {
		return _states;
	}

	CArray<CWindow*>& S_Core::WindowManager( void ) {
		return _windows;
	}

	S_Core& S_Core::GetInstance( void ) {
		static S_Core instance;
		return instance;
	}

}