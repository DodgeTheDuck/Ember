
#include "c_camera.h"

CCamera::CCamera( void ) : CEntity( ) {
	Init( );
}

void CCamera::Init( void ) {

}

void CCamera::Tick( void ) {
	_rigidBody.transform._position = Vector2( 800, 512 ) - _target->transform._position;
}

void CCamera::Draw( void ) {

}

void CCamera::SetTarget( CRigidBody * body ) {
	_target = body;
}