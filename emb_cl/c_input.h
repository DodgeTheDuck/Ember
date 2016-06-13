#pragma once

#define MAX_CONTROL_NAMES 8
#define MAX_AXIS_NAMES 8
#include "c_window.h"

namespace EmbCL {

	enum e_AxisName {
		AN_mouse_x,
		AN_mouse_y
	};

	enum e_ControlName {
		CN_forward,
		CN_backward,
		CN_turn_left,
		CN_turn_right,
		CN_strafe_left,
		CN_strafe_right,
		CN_fire
	};

	class SControls {

		public:
		SControls( void ) { _lockMouse = false; };

		void Update( CWindow * window ) {
			GetAsyncKeyState( 0x57 ) ? SetControl( CN_forward, true ) : SetControl( CN_forward, false );
			GetAsyncKeyState( 0x53 ) ? SetControl( CN_backward, true ) : SetControl( CN_backward, false );
			GetAsyncKeyState( 0x41 ) ? SetControl( CN_strafe_left, true ) : SetControl( CN_strafe_left, false );
			GetAsyncKeyState( 0x44 ) ? SetControl( CN_strafe_right, true ) : SetControl( CN_strafe_right, false );
			GetAsyncKeyState( 0x20 ) ? SetControl( CN_fire, true ) : SetControl( CN_fire, false );

			Vector2 currentMousePos = GetMousePos( window->GetHandle( ) );

			t_real xdelta = currentMousePos.x - _origin.x;
			t_real ydelta = currentMousePos.y - _origin.y;

			SetAxis( AN_mouse_x, xdelta );
			SetAxis( AN_mouse_y, ydelta );

			if( _lockMouse ) {
				window->SetMousePos( _origin.x, _origin.y );
			}



		}

		bool TestControl( e_ControlName control ) { return _names[control]; }
		bool TestImmediate( int code ) { return( GetAsyncKeyState( code ) & 0x8000 );  }
		void SetControl( e_ControlName control, bool state ) { _names[control] = state; }

		t_real GetAxis( e_AxisName axis ) { return _axis[axis]; }
		void SetAxis( e_AxisName axis, t_real value ) { _axis[axis] = value; }

		void EnableMouseLock( bool state ) {
			_lockMouse = state;
			ShowCursor( !state );
		}

		void SetMouseOrigin( Vector2 origin ) {
			_origin = origin;
		}

		Vector2 GetMousePos( HWND window ) {
			POINT p;
			if( GetCursorPos( &p ) ) {
				if( ScreenToClient( window, &p ) ) {
					return Vector2( p.x, p.y );
				}
			}
		}

		void Reset( void ) {
			for( t_uint i = 0; i < MAX_CONTROL_NAMES; i++ ) _names[i] = false;
			for( t_uint i = 0; i < MAX_AXIS_NAMES; i++ ) _axis[i] = false;
		};

		static SControls& GetInstance( void ) {
			static SControls control;
			return control;
		}

		private:

		bool _lockMouse;
		Vector2 _origin;

		bool _names[MAX_CONTROL_NAMES];
		t_real _axis[MAX_AXIS_NAMES];

		public:

		SControls( SControls const& ) = delete;
		void operator=( SControls const& ) = delete;

	};

}