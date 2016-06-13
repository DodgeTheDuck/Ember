
#include "c_fire.h"
#include <c_wrapper.h>

t_byte timer;


CFire::CFire( void ) {

	_bounds = t_size2D_i( 64, 64 );

	_temp = (t_byte**) calloc( _bounds.h, sizeof( t_byte* ) );
	for( t_uint i = 0; i < _bounds.w; i++ ) {
		_temp[i] = (t_byte*) calloc( _bounds.w, sizeof( t_byte ) );
	}

	_oxy = (t_byte**) calloc( _bounds.h, sizeof( t_byte* ) );
	for( t_uint i = 0; i < _bounds.w; i++ ) {
		_oxy[i] = (t_byte*) calloc( _bounds.w, sizeof( t_byte ) );
	}

	for( t_uint j = 0; j < _bounds.w; j++ ) {
		for( t_uint i = 0; i < _bounds.w; i++ ) {
			_oxy[i][j] = 255;
		}
	}

	_temp[_bounds.w / 2][_bounds.h - 1] = 200;

	timer = 0;

}

void CFire::Tick( void ) {

	timer++;

	if( timer >= TARGET_FPS / 10 ) {
		timer = 0;

		t_uint i = _bounds.w / 2;
		t_uint j = _bounds.h - 1;

		SamplePoint( i, j, 0 );

		for( t_uint j = 0; j < _bounds.h; j++ ) {
			for( t_uint i = 0; i < _bounds.w; i++ ) {
				_oxy[i][j] = Math::Clamp( _oxy[i][j] + 32, 0, 255 );
				_temp[i][j] = Math::Clamp( _temp[i][j] - 8, 0, 255 );
			}
		}

		_temp[_bounds.w / 2][_bounds.h - 1] = 200;
		_temp[_bounds.w / 2 - 1][_bounds.h - 1] = 200;
		_temp[_bounds.w / 2 + 1][_bounds.h - 1] = 200;
	}

}

void CFire::Draw( void ) {

	for( t_uint j = 0; j < _bounds.h; j++ ) {
		for( t_uint i = 0; i < _bounds.w; i++ ) {
			EmbR::SetColor( 1.0 - _temp[i][j] / 255.0, 1.0 - _temp[i][j] / 64.0, _temp[i][j] / 255.0, _temp[i][j] / 255.0 );
			EmbR::DrawPoint( { (t_real) ( 128 + i * 4 ), (t_real) ( 128 + j * 4 ) } );
		}
	}

}

bool CFire::SamplePoint( t_uint x, t_uint y, t_uint depth ) {

	if( x < 1 ) x = 1;
	if( x > _bounds.w - 2 ) x = _bounds.w - 2;
	if( y < 1 ) y = 1;
	if( y > _bounds.h - 1 ) y = _bounds.h - 1;

	t_byte self = _temp[x][y];

	if( self == 0 ) return true;

	t_byte above = _temp[x][y - 1];
	t_byte above_l = _temp[x - 1][y - 1];
	t_byte above_r = _temp[x + 1][y - 1];

	t_byte delta = self - above;
	t_byte delta_l = self - above_l;
	t_byte delta_r = self - above_r;

	t_byte oxy = _oxy[x][y];
	t_byte oxy_above = _oxy[x][y - 1];
	t_byte oxy_l = _oxy[x - 1][y - 1];
	t_byte oxy_r = _oxy[x + 1][y - 1];


	t_byte transfer_l = delta_l / 4 * ( oxy_l / 255.0 );
	t_byte transfer_r = delta_r / 4 * ( oxy_r / 255.0 );
	t_byte transfer = ( delta / 2 ) - transfer_l - transfer_r;

	_oxy[x][y - 1] -= transfer;
	_oxy[x - 1][y - 1] -= transfer_l;
	_oxy[x + 1][y - 1] -= transfer_r;

	if( delta > 32 ) depth++;
	if( delta_l > 16 ) depth++;
	if( delta_r > 16 ) depth++;

	_temp[x][y] = Math::Clamp( self - transfer, 0, 255 );
	_temp[x][y - 1] = Math::Clamp( above + transfer, 0, 255 );
	_temp[x - 1][y - 1] = Math::Clamp( above_l + transfer_l, 0, 255 );
	_temp[x + 1][y - 1] = Math::Clamp( above_r + transfer_r, 0, 255 );

	if( depth <= 8 ) SamplePoint( x, y - 1, depth );
	if( depth <= 8 ) SamplePoint( x - 1, y - 1, depth );
	if( depth <= 8 ) SamplePoint( x + 1, y - 1, depth );

	return true;

}