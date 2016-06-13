#pragma once

#include <c_common.h>
#include "c_entity.h"

class CCamera : public CEntity {

	public:

	CCamera( void );
	virtual void Init( void );
	virtual void Tick( void );
	virtual void Draw( void );
	void SetTarget( CRigidBody * body );

	private:
	CRigidBody * _target;

};