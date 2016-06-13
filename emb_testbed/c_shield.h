#pragma once

#include "c_entity.h"

class CShield : public CEntity {

	public:
	CShield( void );
	virtual void Init( void );
	virtual void Tick( void );
	virtual void Draw( void );
	virtual void OnCollision( s_colInfo * info );
	private:

};