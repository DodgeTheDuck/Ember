
#include "c_wrapper.h"
#include <GL\glew.h>

HDC		EmbR::_device = 0;
HGLRC	EmbR::_context = 0;

void EmbR::Init( HWND hwnd ) {

	_device = GetDC( hwnd );
	_context = wglCreateContext( _device );

	RECT size;
	GetWindowRect( hwnd, &size );

	wglMakeCurrent( _device, _context );

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	glShadeModel( GL_SMOOTH );
	glClearColor( 0, 0, 0, 0 );
	glClearDepth( 1.0 );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );

	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	glewInit( );

}

void EmbR::Clear( void ) {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void EmbR::Swap( void ) {
	SwapBuffers( _device );
}