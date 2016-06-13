#pragma once

#include <c_defs.h>

class CHull;
typedef t_uint t_tag;

class CRigidBody {

	public:
	CRigidBody( void );
	void Tick( void );
	void Impulse( t_real force, t_real direction, Vector2 offset = { 0, 0 } );

	void SolveElastic( CRigidBody * other );

	Vector2 GetVelocity( void );
	t_tag GetTag( void );
	void SetTag( t_tag tag );

	t_real Forward( void );

	Transform2D		transform;
	CHull *			hull;
	t_real			mass;


	private:
	Vector2			_origin;
	Vector2			_velocity;
	Vector2			_acceleration;
	t_real			_angularAcceleration;
	t_real			_angularVelocity;
	t_tag			_tag;


};