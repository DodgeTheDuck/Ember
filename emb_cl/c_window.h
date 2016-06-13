#pragma once

#include "c_common.h"

namespace EmbCL {

	class CWindow {

		public:
		CWindow( t_rect_i bounds, t_c_pstring title, t_c_pstring uniqueId, HWND parent = NULL, t_c_pstring menuName = NULL, WNDPROC wndproc = NULL );
		void Show( void );
		void Update( void );
		void Close( void );
		void SetMousePos( t_real x, t_real y );
		t_rect_i GetRect( void );
		HWND GetHandle( void );

		private:
		static LRESULT CALLBACK _HandleEvents( HWND, UINT, WPARAM, LPARAM );
		HWND	_windowHandle;
		HDC		_deviceContext;

	};

}

