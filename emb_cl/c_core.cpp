
#include "c_core.h"
#include "c_state.h"
#include "c_window.h"
#include "c_input.h"
#include <c_timing.h>
#include <c_wrapper.h>

namespace EmbCL {

	SCore::SCore( void ) { }

	void SCore::Init( void ) {

		AllocConsole( );
		freopen( "CONOUT$", "w", stdout );

		/*CWindow * window = new CWindow( { 0, 0, 1024, 1024 }, "Ember Engine", "0" );
		_windows.Push( window );
		_windows[0]->Show( );*/
		EmbR::Init( );

		_states.top( )->Init( );

		_frameTimer = CStopwatch( );
		_frameTimer.Start( );

	}

	void SCore::Run( void ) {

		while( IsWindow( _windows[0]->GetHandle( ) ) ) {

			_frameTimer.Stop( );
			_frameDeltaAccumulator += _frameTimer.Read( ) / 1000.0;
			_secondCounter += _frameTimer.Read( );
			_frameTimer.Reset( );
			_frameTimer.Start( );

			t_real updateThreshold = ( 1.0 / TARGET_FPS ) ;
			
			if( _frameDeltaAccumulator >= updateThreshold ) {
				_Tick( );
				_Draw( );
				_frameDeltaAccumulator = 0;
				_frameCount++;
			}

			if( _secondCounter > 1000.0 ) {
				std::cout << "FPS: " << _frameCount << std::endl;
				_frameCount = 0;
				_secondCounter = 0;
			}

			MSG msg;

			if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) {
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}

			_windows[0]->Update( );

		}

	}

	void SCore::Shutdown( void ) {

	}

	void SCore::_Tick( void ) {
		SControls::GetInstance( ).Update( _windows[0] );
		_states.top( )->Tick( );
	}

	void SCore::_Draw( void ) {
		EmbR::Clear( );
		_states.top( )->Draw( );
		EmbR::Swap( );
	}

	std::stack<CState*>& SCore::StateManager( void ) {
		return _states;
	}

	std::vector<CWindow*>& SCore::WindowManager( void ) {
		return _windows;
	}

	SCore& SCore::GetInstance( void ) {
		static SCore instance;
		return instance;
	}

}