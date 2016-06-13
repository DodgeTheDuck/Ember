#pragma once

#include <c_common.h>

class CFire {

	public:
	CFire( void );
	void Tick( void );
	void Draw( void );
	bool SamplePoint( t_uint x, t_uint y, t_uint depth );
	private:
	t_size2D_i _bounds;
	t_byte ** _temp;
	t_byte ** _oxy;

};