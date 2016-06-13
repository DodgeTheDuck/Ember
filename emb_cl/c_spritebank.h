#pragma once

#include "c_common.h"

class CSprite;

typedef t_uint t_spriteHandle;

class CSpriteBank {

	public:
	t_spriteHandle Load( const char * filepath );
	t_spriteHandle Add( CSprite * sprite );
	CSprite * Get( t_spriteHandle handle );
	static CSpriteBank& GetInstance( void );

	private:
	static std::vector<CSprite*> _bank;
		
};