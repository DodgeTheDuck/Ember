
#include "c_laser.h"
#include <c_spritebank.h>
#include "c_entman.h"
#include "c_emitter.h"
#include <c_shape.h>

CLaser::CLaser( Vector2 from, t_real focalDistance ) : CEntity( ) {
	_rigidBody.transform._position = from;
	_focalDistance = focalDistance;
	_offset = 3;
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
	emit.spread = 360;
	emit.type = EMIT_BURST;
	emit.interval = 0;
	emit.minSpeed = 0.8;
	emit.maxSpeed = 1.2;
	emit.count = 32;
	emit.lifespan = 1;

	_emitter = new CEmitter( { 512, 512 }, emit, info );

	entMan.Add( _emitter );

	Init( );
}

void CLaser::Init( void ) {
	AllocateSprites( 2 );
	_sprite[0] = CSpriteBank::GetInstance( ).Get( SPRH_LASER );
	_sprite[0]->SetColor( { 0.5, 0.5, 1.0, 1.0 } );
	_sprite[0]->SetOffset( { 0, -_offset } );
	_sprite[0]->SetAngle( 0.4 );
	_sprite[0]->SetBlendMode( BLEND_ADD );
	_sprite[0]->SetOrigin( { -_focalDistance / 2, 0.0 } );
	_sprite[0]->SetScale( { _focalDistance, 1 } );
	_sprite[1] = CSpriteBank::GetInstance( ).Get( SPRH_LASER );
	_sprite[1]->SetColor( { 0.5, 0.5, 1.0, 1.0 } );
	_sprite[1]->SetOffset( { 0, _offset } );
	_sprite[1]->SetOrigin( { -_focalDistance / 2, 0.0 } );
	_sprite[1]->SetAngle( -0.4 );
	_sprite[1]->SetBlendMode( BLEND_ADD );
	_sprite[1]->SetScale( { _focalDistance, 1 } );
}

void CLaser::Tick( void ) {

	t_real angle = atan2( _offset, _focalDistance );

	_sprite[0]->SetAngle( Math::Degrees( angle ) );
	_sprite[1]->SetAngle( Math::Degrees( -angle ) );

	CEntity::Tick( );
}

void CLaser::Draw( void ) {
	CEntity::Draw( );
}

CLaser::~CLaser( ) {

}