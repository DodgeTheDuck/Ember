#pragma once

#include "c_entity.h"

class CEmitter;

class CProjectile : public CEntity {

	public:
	CProjectile( Vector2 pos = { 0,0 }, t_real direction = 0 );
	virtual ~CProjectile( void );
	virtual void Init( void );
	virtual void Tick( void );
	virtual void Draw( void );
	private:
	CEmitter * _emitter;

};