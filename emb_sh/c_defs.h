#pragma once

#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <string>
#include <strsafe.h>
#include <random>

#define EMB_CL_API	__declspec( dllexport )
#define EMB_SH_API  __declspec( dllexport )
#define EMB_R_API	__declspec( dllexport )
#define STRING _T

#define PI 3.1415926

#define TARGET_FPS 144.0

namespace EMB {
	static HINSTANCE hInstance;
}

typedef LARGE_INTEGER			t_int64;
typedef int						t_int32;
typedef short					t_int16;
typedef char					t_int8;
typedef unsigned int			t_uint;
typedef int						t_size;
typedef double					t_real;

typedef std::wstring			t_wstring;
typedef const std::wstring		t_c_wstring;
typedef LPCSTR					t_c_pstring;

typedef BYTE					t_byte;

struct t_rect_i {
	t_rect_i( t_int32 x = 0, t_int32 y = 0, t_int32 w = 0, t_int32 h = 0 ) :
		x( x ), y( y ), w( w ), h( h ) { };
	t_int32 x, y, w, h;
};

struct t_rect_r {
	t_rect_r( t_real x = 0, t_real y = 0, t_real w = 0, t_real h = 0 ) :
		x( x ), y( y ), w( w ), h( h ) { };
	t_real x, y, w, h;
};

struct t_size2D_i {
	t_size2D_i( t_int32 w = 0, t_int32 h = 0 ) :
		 w( w ), h( h ) { };
	t_int32 w, h;
};

struct t_color4_r {
	t_color4_r( t_real r = 1.0, t_real g = 1.0, t_real b = 1.0, t_real a = 1.0 ) :
		r( r ), g( g ), b( b ), a( a ) { };
	t_real r, g, b, a;
};

struct Vector2 {

	Vector2( void ) : x( 0 ), y( 0 ) { };
	Vector2( t_real x, t_real y ) : x( x ), y( y ) { };

	t_real x;
	t_real y;

	t_real		Length( void ) { return sqrt( ( ( x * x ) + ( y * y ) ) ); }

	void Normalise( void ) {
		t_real length = Length( );
		if( length == 0 ) return;
		x = x / length;
		y = y / length;
	}

	Vector2 Normal( void ) {
		t_real length = Length( );
		if( length == 0 || isinf( length ) || isnan( length ) ) return { 0, 0 };
		return { x / length, y / length };
	}

	t_real Dot( Vector2 &other ) {
		return ( x * other.x ) + ( y * other.y );
	}

	t_real Direction( void ) {
		Vector2 buffer = Normal( );
		return atan2( buffer.y, buffer.x );
	}

	void Zero( void ) {
		x = 0;
		y = 0;
	}

	bool		operator==( const Vector2& rhs ) { return ( x == rhs.x && y == rhs.y ); };

	Vector2		operator+( const Vector2& rhs ) { return Vector2( x + rhs.x, y + rhs.y ); };
	void		operator+=( const Vector2& rhs ) { x += rhs.x; y += rhs.y; };

	Vector2		operator-( const Vector2& rhs ) { return Vector2( x - rhs.x, y - rhs.y ); };
	Vector2		operator-( void ) { return Vector2( -x, -y ); };
	void		operator-=( const Vector2& rhs ) { x -= rhs.x; y -= rhs.y; };

	Vector2		operator*( const t_real& rhs ) { return { x * rhs, y * rhs }; }

};

struct Vector3 {

	Vector3( void ) : x( 0 ), y( 0 ), z( 0 ) { };
	Vector3( t_real x, t_real y, t_real z ) : x( x ), y( y ), z( z ) { };

	float x;
	float y;
	float z;

	t_real Length( void ) { return sqrt( ( ( x * x ) + ( y * y ) + ( z * z ) ) ); }

	void Normalise( void ) {
		t_real length = Length( );
		x = x / length;
		y = y / length;
		z = z / length;
	}

	Vector3 Cross( Vector3 &other ) {
		return Vector3(
			( y*other.z ) - ( z*other.y ),
			( z*other.x ) - ( x*other.z ),
			( x*other.y ) - ( y * other.x )
		);
	}

	t_real Dot( Vector3 &other ) {
		return ( x * other.x ) + ( y * other.y ) + ( z * other.z );
	}

	void Zero( void ) {
		x = 0;
		y = 0;
		z = 0;
	}

	Vector2 ToVec2( void ) { return Vector2( x, y ); }

	bool		operator==( const Vector3& rhs ) { return ( x == rhs.x && y == rhs.y && y == rhs.z ); };

	Vector3		operator+( const Vector3& rhs ) { return Vector3( x + rhs.x, y + rhs.y, z + rhs.z ); };
	void		operator+=( const Vector3& rhs ) { x += rhs.x; y += rhs.y; z += rhs.z; };

	Vector3 	operator-( const Vector3& rhs ) { return Vector3( x - rhs.x, y - rhs.y, z - rhs.z ); };
	void		operator-=( const Vector3& rhs ) { x -= rhs.x; y -= rhs.y; z -= rhs.z; };

};

struct Vector4 {

	Vector4( void ) : x( 0 ), y( 0 ), z( 0 ), w( 0 ) { };
	Vector4( t_real x, t_real y, t_real z, t_real w ) : x( x ), y( y ), z( z ), w( w ) { };

	float x;
	float y;
	float z;
	float w;

	Vector3 ToVec3( void ) { return Vector3( x, y, z ); }
	Vector2 ToVec2( void ) { return Vector2( x, y ); }

	bool		operator==( const Vector4& rhs ) { return ( x == rhs.x && y == rhs.y && y == rhs.z && w == rhs.w ); };

	Vector4		operator+( const Vector4& rhs ) { return Vector4( x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w ); };
	void		operator+=( const Vector4& rhs ) { x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w; };

	Vector4 	operator-( const Vector4& rhs ) { return Vector4( x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w ); };
	void		operator-=( const Vector4& rhs ) { x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w; };

};

struct Vertex2 {
	Vertex2( t_real x, t_real y ) : location( { x,y } ) { };
	Vertex2( void ) { };
	Vector2 location;
};

struct Vertex3 {
	Vertex3( t_real x, t_real y, t_real z ) : location( { x,y,z } ) { };
	Vertex3( void ) { };
	Vector3 location;
	Vector2 uv;
	Vector3 normal;
	t_color4_r color;
};

struct Transform2D {
	Vector2		_position = { 0, 0 };
	t_real		_angle = 0;
	t_real		_scale = 1.0;
};

namespace Math {

	static t_real Distance( Vector2 p0, Vector2 p1 ) {
		return sqrt( ( p1.x - p0.x ) * ( p1.x - p0.x ) + ( p1.y - p0.y ) * ( p1.y - p0.y ) );
	}

	static t_real Angle( Vector2 p0, Vector2 p1 ) {
		t_real dx = p1.x - p0.x;
		t_real dy = p1.y - p0.y;
		return atan2( dy, dx );
	}

	static t_real Clamp( t_real value, t_real min, t_real max ) {
		if( value > max ) return max;
		if( value < min ) return min;
		return value;
	}

	static t_real RandomRange( t_real min, t_real max ) {
		std::random_device rd;
		std::mt19937 e2( rd( ) );
		std::uniform_real_distribution<> dist( min, max );
		return dist( e2 );
	}

	static t_real Radians( t_real degrees ) {
		return degrees * PI / 180.0;
	}

	static t_real Degrees( t_real radians ) {
		return radians * 180.0 / PI;
	}

	static t_real Interp1( t_real T, t_real t, t_real x, t_real y ) {
		return t * ( ( y - x ) / T ) + x;
	}

}

static void ErrorExit( LPTSTR lpszFunction ) {
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError( );

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
		(LPTSTR) &lpMsgBuf,
		0, NULL );

	// Display the error message and exit the process

	lpDisplayBuf = (LPVOID) LocalAlloc( LMEM_ZEROINIT,
		( lstrlen( (LPCTSTR) lpMsgBuf ) + lstrlen( (LPCTSTR) lpszFunction ) + 40 ) * sizeof( TCHAR ) );
	StringCchPrintf( (LPTSTR) lpDisplayBuf,
					 LocalSize( lpDisplayBuf ) / sizeof( TCHAR ),
					 TEXT( "%s failed with error %d: %s" ),
					 lpszFunction, dw, lpMsgBuf );
	MessageBox( NULL, (LPCTSTR) lpDisplayBuf, TEXT( "Error" ), MB_OK );

	LocalFree( lpMsgBuf );
	LocalFree( lpDisplayBuf );
	ExitProcess( dw );
}