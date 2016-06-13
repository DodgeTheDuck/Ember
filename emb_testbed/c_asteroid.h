#pragma once

#include "c_entity.h"

class CAsteroid : public CEntity {

	public:
	CAsteroid( Vector2 pos = { 0,0 } );
	virtual void Init( void );
	virtual void Tick( void );
	virtual void Draw( void );

};