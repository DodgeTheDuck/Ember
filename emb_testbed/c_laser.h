#pragma once

#include "c_entity.h"

class CEmitter;

class CLaser : public CEntity {

	public:
	CLaser( Vector2 from, t_real focalDistance );
	virtual ~CLaser( void );
	virtual void Init( void );
	virtual void Tick( void );
	virtual void Draw( void );
	private:
	t_real _focalDistance;
	t_real _offset;
	CEmitter * _emitter;

};