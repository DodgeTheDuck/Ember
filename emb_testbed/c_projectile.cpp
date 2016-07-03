
#include "c_projectile.h"
#include "c_hull.h"
#include <c_image.h>
#include "c_emitter.h"
#include "c_entman.h"

CProjectile::CProjectile( Vector2 pos, t_real direction ) : CEntity( ) {
	_rigidBody.transform._position = pos;
	_rigidBody.Impulse( 5, direction );
	_rigidBody.mass = 1.0;

	CEntMan& entMan = CEntMan::GetInstance( );

	SPartInfo info;
	info.minLifespan = 20;
	info.maxLifespan = 60;
	info.startColor = { 1.0, 1.0, 0.0, 1.0 };
	info.startVariance = { 0.2, 0.1, 0.0, 0.2 };
	info.endColor = { 0.2, 0.25, 0.2, 0.0 };
	info.endVariance = { 0.1, 0.05, 0.2, 0.05 };
	info.minScale = 0.1;
	info.maxScale = 0.4;

	SEmitInfo emit;
	emit.spread = 90;
	emit.type = EMIT_STREAM;
	emit.interval = 2;
	emit.minSpeed = 0.8;
	emit.maxSpeed = 1.2;

	_emitter = new CEmitter( { 512, 512 }, emit, info );

	entMan.Add( _emitter );

	Init( );
}

void CProjectile::Init( void ) {
	AllocateSprites( 1 );
	_sprite[0] = CSpriteBank::GetInstance( ).Get( SPRH_PARTICLE );
	_sprite[0]->SetColor( { 1.0, 1.0, 0.3, 1.0 } );
	_rigidBody.hull = new CHullCircle( 4, &_rigidBody.transform );
}

void CProjectile::Tick( void ) {
	CEntity::Tick( );
	if( _rigidBody.transform._position.x < -32 ) CEntMan::GetInstance( ).Kill( this );
	else if( _rigidBody.transform._position.x > 1632 ) CEntMan::GetInstance( ).Kill( this );
	else if( _rigidBody.transform._position.y < -32 ) CEntMan::GetInstance( ).Kill( this );
	else if( _rigidBody.transform._position.y > 1056 ) CEntMan::GetInstance( ).Kill( this );
	_emitter->SetPosition( _rigidBody.transform._position );
}

void CProjectile::Draw( void ) {
	CEntity::Draw( );
}

CProjectile::~CProjectile( void ) {
	CEntMan::GetInstance( ).Kill( _emitter );
}