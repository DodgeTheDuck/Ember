
#include "c_entity.h"
#include "c_hull.h"
#include "c_entman.h"

CEntity::CEntity( void ) {

}

void CEntity::Init( void ) {

}

void CEntity::Tick( void ) {

	_rigidBody.Tick( );

}

void CEntity::SetPosition( Vector2 newPosition ) {
	_rigidBody.transform._position = newPosition;
}

void CEntity::Draw( void ) {
	EmbR::PushTransform( _rigidBody.transform );
	if( _sprite ) _sprite->Draw( );
	EmbR::PopTransform( );
	//if( _rigidBody.hull ) _rigidBody.hull->Draw( );
}

void CEntity::OnCollision( s_colInfo * info ) {

}

CRigidBody& CEntity::GetRigidBody( void ) {
	return _rigidBody;
}

CEntity::~CEntity( void ) {
	if( _sprite ) delete _sprite;
}