
#include "c_camera.h"

CCamera::CCamera( void ) : CEntity( ) {
	Init( );
}

void CCamera::Init( void ) {

}

void CCamera::Tick( void ) {
	t_real scaleFactor = 1.0 - _target->GetVelocity( ).Length( ) / 25.0;
	_rigidBody.transform._scale = { scaleFactor, scaleFactor };

	Vector2 otherVel = _target->GetVelocity( );
	Vector2 thisPos = _rigidBody.transform._position + Vector2( 800, 512 );
	Vector2 otherPos = _target->transform._position;

	_rigidBody.transform._position = ( Vector2( 800, 512 ) - _target->transform._position * scaleFactor );
}

void CCamera::Draw( void ) {

}

void CCamera::SetTarget( CRigidBody * body ) {
	_target = body;
}