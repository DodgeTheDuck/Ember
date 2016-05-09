
#include "c_window.h"
#include "c_core.h"

namespace EmbCL {

	CWindow::CWindow( t_rect_i bounds, t_c_pstring title, t_c_pstring uniqueId ) {

		WNDCLASSEX wcex;

		wcex.cbSize = sizeof( WNDCLASSEX );
		wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wcex.lpfnWndProc = _HandleEvents;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = EMB::hInstance;
		wcex.hIcon = LoadIcon( EMB::hInstance, IDI_APPLICATION );
		wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
		wcex.hbrBackground = (HBRUSH) ( COLOR_WINDOW + 1 );
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = uniqueId;
		wcex.hIconSm = LoadIcon( wcex.hInstance, IDI_APPLICATION );

		if( !RegisterClassEx( &wcex ) ) {
			MessageBox( NULL, STRING( "Call to RegisterClassEx failed!" ), STRING( "RIP" ), NULL );
			return;
		}

		_windowHandle = CreateWindow (
			wcex.lpszClassName,
			title,
			WS_OVERLAPPEDWINDOW,
			bounds.x,
			bounds.y,
			bounds.w,
			bounds.h,
			NULL,
			NULL,
			EMB::hInstance,
			NULL
		);

		if( !_windowHandle ) {
			MessageBox( NULL, STRING( "Call to CreateWindow Failed" ), STRING( "RIP" ), NULL );
			return;
		}

		_deviceContext = GetDC( _windowHandle );

		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof( PIXELFORMATDESCRIPTOR ),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,		//Flags
			PFD_TYPE_RGBA,													//The kind of framebuffer. RGBA or palette.
			32,																//Colordepth of the framebuffer.
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,																//Number of bits for the depthbuffer
			8,																//Number of bits for the stencilbuffer
			0,																//Number of Aux buffers in the framebuffer.
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		int pfn = ChoosePixelFormat( _deviceContext, &pfd );

		if( !pfn ) {
			MessageBox( NULL, STRING( "Could not find Pixel Format" ), STRING( "RIP" ), NULL );
			return;
		}

		SetPixelFormat( _deviceContext, pfn, &pfd );

		RECT rcClient, rcWind;
		POINT ptDiff;
		GetClientRect( _windowHandle, &rcClient );
		GetWindowRect( _windowHandle, &rcWind );
		ptDiff.x = ( rcWind.right - rcWind.left ) - rcClient.right;
		ptDiff.y = ( rcWind.bottom - rcWind.top ) - rcClient.bottom;
		MoveWindow( _windowHandle, rcWind.left, rcWind.top, bounds.w + ptDiff.x, bounds.h + ptDiff.y, TRUE );

	}

	void CWindow::Show( void ) {
		ShowWindow( _windowHandle, 1 );
	}

	void CWindow::Update( void ) {
		UpdateWindow( _windowHandle );
	}

	void CWindow::SetMousePos( t_real x, t_real y ) {

		POINT p;

		p.x = x;
		p.y = y;

		ClientToScreen( _windowHandle, &p );
		SetCursorPos( p.x, p.y );

	}

	HWND CWindow::GetHandle( void ) {
		return _windowHandle;
	}

	LRESULT CWindow::_HandleEvents( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {

		PAINTSTRUCT ps;
		HDC hdc;

		/*Controls.Reset( );*/

		switch( uMsg ) {
			case WM_PAINT:
				break;
			case WM_DESTROY:
				PostQuitMessage( 0 );
				break;
			case WM_KEYDOWN:
				break;
			case WM_CHAR:
				break;
			default:
				return DefWindowProc( hWnd, uMsg, wParam, lParam );
				break;
		}

		return 0;

	}

	t_rect_i CWindow::GetRect( void ) {
		RECT rect;
		GetWindowRect( _windowHandle, &rect );
		return t_rect_i( rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top );
	}

}

