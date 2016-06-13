
#include "c_asteroid.h"
#include "c_hull.h"
#include <c_image.h>
#include "c_entman.h"

CAsteroid::CAsteroid( Vector2 pos ) {
	_rigidBody.transform._position = pos;
	Init( );
}

void CAsteroid::Init( void ) {
	
	_rigidBody.Impulse( 0.2, 0, { 1, 0 } );
	_rigidBody.mass = 50.0;
	_rigidBody.transform._scale = 0.75;
	_sprite = CSpriteBank::GetInstance( ).Get( SPRH_ASTEROID );
	_rigidBody.hull = new CHullCircle( 48, &_rigidBody.transform );

	if( _rigidBody.transform._position.x < -32 ) CEntMan::GetInstance( ).Kill( this );
	if( _rigidBody.transform._position.x > 1632 ) CEntMan::GetInstance( ).Kill( this );
	if( _rigidBody.transform._position.y < -32 ) CEntMan::GetInstance( ).Kill( this );
	if( _rigidBody.transform._position.y > 1056 ) CEntMan::GetInstance( ).Kill( this );

}

void CAsteroid::Tick( void ) {
	CEntity::Tick( );

}

void CAsteroid::Draw( void ) {
	CEntity::Draw( );
}