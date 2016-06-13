#pragma once

#include "c_entity.h"
#include <c_sprite.h>
#include <c_timing.h>

class CShield;
class CEmitter;

class CPlayer : public CEntity {

	public:

	CPlayer( );

	virtual void Init( void );
	virtual void Tick( void );
	virtual void Draw( void );

	private:
	bool _reloading;
	t_real _reloadTimer;
	CEmitter * _thruster;
	CShield * _shield;

};