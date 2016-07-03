#pragma once

#include <c_common.h>

class CRigidBody;
class CEntity;

class CWeapon {

	public:

	virtual void Fire( CRigidBody& from ) = 0;
	virtual void Wait( void ) = 0;

	private:


};

class CWepBlaster : public CWeapon {

	public:

	virtual void Fire( CRigidBody& from );
	virtual void Wait( void );
	
	protected:

	bool _reloading = false;
	t_real _reloadCounter = 0;
	t_real _reloadTime = 10;

};

class CWepLaser : public CWeapon {

	public:

	virtual void Fire( CRigidBody& from );
	virtual void Wait( void );

	protected:

	CEntity * _laser;

};