
#include "c_rigidBody.h"
#include "c_entity.h"
#include "c_entman.h"
#include "c_hull.h"
#include <vector>

CRigidBody::CRigidBody( void ) {
	_angularAcceleration = 0;
	_angularVelocity = 0;
	hull = NULL;
}

void CRigidBody::Tick( void ) {

	_velocity += _acceleration;
	transform._position += _velocity;
	_acceleration = Vector2( 0, 0 );

	_angularVelocity += _angularAcceleration;
	transform._angle += _angularVelocity;
	_angularAcceleration = 0;

}

t_real CRigidBody::Forward( void ) {
	return transform._angle;
}


t_tag CRigidBody::GetTag( void ) {
	return _tag;
}

void CRigidBody::SetTag( t_tag tag ) {
	_tag = tag;
}

void CRigidBody::Impulse( t_real force, t_real direction, Vector2 offset ) {

	t_real xCoeff = abs( 1.0 / ( 1.0 / offset.x ) );
	t_real yCoeff = abs( 1.0 / ( 1.0 / offset.y ) );

	_acceleration.x += cos( Math::Radians( direction ) ) * force * ( 1.0 - xCoeff );
	_acceleration.y += sin( Math::Radians( direction ) ) * force * ( 1.0 - yCoeff );

	Vector2 angularCoeff = { xCoeff, yCoeff };
	angularCoeff.Normalise( );
	t_real angularLength = angularCoeff.Length( );

	if( offset.x > 0 )
		_angularAcceleration += force * angularCoeff.Length( );
	else if( offset.x < 0 )
		_angularAcceleration -= force * angularCoeff.Length( );

}

Vector2 CRigidBody::GetVelocity( void ) {
	return _velocity;
}