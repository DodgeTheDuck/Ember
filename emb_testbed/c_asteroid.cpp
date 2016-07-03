
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
	_rigidBody.mass = 5000;
	_rigidBody.transform._scale = { 0.75, 0.75 };

	AllocateSprites( 1 );
	_sprite[0] = CSpriteBank::GetInstance( ).Get( SPRH_ASTEROID );
	_rigidBody.hull = new CHullCircle( 48, &_rigidBody.transform );

}

void CAsteroid::Tick( void ) {

	CEntity::Tick( );

	t_color4_r c = _sprite[0]->GetColor( );

	if( c.r > 1.0 ) c.r -= 0.04;
	if( c.g > 1.0 ) c.g -= 0.02;
	if( c.b > 1.0 ) c.b -= 0.01;

	_sprite[0]->SetColor( c );

	if( _rigidBody.transform._position.x < -32 ) CEntMan::GetInstance( ).Kill( this );
	if( _rigidBody.transform._position.x > 1632 ) CEntMan::GetInstance( ).Kill( this );
	if( _rigidBody.transform._position.y < -32 ) CEntMan::GetInstance( ).Kill( this );
	if( _rigidBody.transform._position.y > 1056 ) CEntMan::GetInstance( ).Kill( this );

}

void CAsteroid::Draw( void ) {
	CEntity::Draw( );
}

void CAsteroid::OnCollision( s_colInfo * info ) {

	t_color4_r c = _sprite[0]->GetColor( );

	c.r += 0.8;
	c.g += 0.4;
	c.b += 0.2;

	_sprite[0]->SetColor( c );

}