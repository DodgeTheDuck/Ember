
#include "c_spritebank.h"
#include <c_sprite.h>
#include <c_image.h>

std::vector<CSprite*> CSpriteBank::_bank;

t_spriteHandle CSpriteBank::Load( const char * filepath ) {
	CSprite * sprite = new CSprite( );
	sprite->CreateFromImage( Emb::CImage( filepath ) );
	return Add( sprite );
}

t_spriteHandle CSpriteBank::Add( CSprite * sprite ) {
	_bank.push_back( sprite );
	return _bank.size();
}

CSprite * CSpriteBank::Get( t_spriteHandle handle ) {
	CSprite * spr = _bank[handle];
	return new CSprite( *spr );
}

CSpriteBank& CSpriteBank::GetInstance( void ) {
	static CSpriteBank bank;
	return bank;
}