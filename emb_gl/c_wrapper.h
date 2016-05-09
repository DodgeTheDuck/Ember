#pragma once

#include <Windows.h>
#include <c_defs.h>

class EmbR {

	public:
	static void Init( HWND hwnd );
	static void Clear( void );
	static void Swap( void );

	private:

	static HGLRC _context;
	static HDC _device;

};