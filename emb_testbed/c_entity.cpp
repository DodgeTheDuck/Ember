
#include "c_entity.h"
#include "c_hull.h"
#include "c_entman.h"

CEntity::CEntity( void ) {
	_enabled = true;
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
	for( t_uint i = 0; i < _spriteCount; i++ ) {
		if( _sprite[i] ) _sprite[i]->Draw( );
	}
	EmbR::PopTransform( );
}

void CEntity::OnCollision( s_colInfo * info ) {

}

CRigidBody& CEntity::GetRigidBody( void ) {
	return _rigidBody;
}

void CEntity::Disable( void ) {
	_enabled = false;
}

void CEntity::Enable( void ) {
	_enabled = true;
}

bool CEntity::IsEnabled( void ) {
	return _enabled;
}

void CEntity::AllocateSprites( t_uint count ) {
	_sprite = (CSprite**)calloc( count, sizeof( CSprite* ) );
	_spriteCount = count;
}

CEntity::~CEntity( void ) {
	if( _sprite ) delete _sprite;
}