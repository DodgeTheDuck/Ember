
#include "c_player.h"
#include <c_input.h>
#include <c_image.h>
#include <c_core.h>
#include "c_entman.h"
#include "c_projectile.h"
#include "c_hull.h"
#include "c_emitter.h"
#include "c_shield.h"
#include "c_weapon.h"

CPlayer::CPlayer( void ) {
	Init( );
}

void CPlayer::Init( void ) {

	CEntMan& entMan = CEntMan::GetInstance( );

	SPartInfo info;
	info.minLifespan = 20;
	info.maxLifespan = 40;
	info.startColor = { 1.0, 0.55, 0.0, 1.0 };
	info.startVariance = { 0.2, 0.1, 0.0, 0.2 };
	info.endColor = { 0.2, 0.25, 1.0, 0.0 };
	info.endVariance = { 0.1, 0.05, 0.2, 0.05 };
	info.minScale = 0.8;
	info.maxScale = 1.2;

	SEmitInfo emit;
	emit.spread = 10;
	emit.type = EMIT_STREAM;
	emit.interval = 2;
	emit.minSpeed = 0.0;
	emit.maxSpeed = 0.0;
	emit.count = 0;
	emit.target = { 0, 0 };

	//_shield = new CShield( );
	//entMan.Add( _shield );

	_thruster = new CEmitter( { 512, 512 }, emit, info );
	entMan.Add( _thruster );

	_weapon = new CWepBlaster( );

	AllocateSprites( 1 );
	_sprite[0] = CSpriteBank::GetInstance( ).Get( SPRH_SHIP0 );

	_rigidBody.hull = new CHullCircle( 40, &_rigidBody.transform );
	_rigidBody.mass = 200;
	_rigidBody.SetTag( 1 );

}

void CPlayer::Tick( void ) {

	EmbCL::SControls& controls = EmbCL::SControls::GetInstance( );

	if( _reloading ) _reloadTimer++;

	if( _reloadTimer >= TARGET_FPS / 16 ) {
		_reloading = false;
		_reloadTimer = 0;
	}

	if( controls.TestControl( EmbCL::CN_forward ) ) { _rigidBody.Impulse( 0.02, _rigidBody.Forward( ) ); _thruster->Enable( ); } else { _thruster->Disable( ); }
	if( controls.TestControl( EmbCL::CN_backward ) ) _rigidBody.Impulse( -0.02, _rigidBody.Forward( ) );
	if( controls.TestControl( EmbCL::CN_strafe_left ) ) _rigidBody.Impulse( 0.02, _rigidBody.Forward( ), { -1, 1 } );
	if( controls.TestControl( EmbCL::CN_strafe_right ) ) _rigidBody.Impulse( 0.02, _rigidBody.Forward( ), { 1, 1 } );
	if( controls.TestControl( EmbCL::CN_fire ) ) { _weapon->Fire( _rigidBody ); } else { _weapon->Wait( ); }

	_thruster->SetDirection( _rigidBody.Forward( ) - 180 );
	_thruster->SetPosition( _rigidBody.transform._position + Vector2( cos( Math::Radians( _rigidBody.Forward( ) ) ) * -60, sin( Math::Radians( _rigidBody.Forward( ) ) ) * -60 ) );

	if( _shield ) _shield->SetPosition( _rigidBody.transform._position );

	CEntity::Tick( );

}

void CPlayer::Draw( void ) {
	CEntity::Draw( );
}