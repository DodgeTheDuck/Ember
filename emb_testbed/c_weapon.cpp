
#include "c_weapon.h"
#include "c_rigidBody.h"
#include "c_entman.h"
#include "c_projectile.h"
#include "c_laser.h"

void CWepBlaster::Fire( CRigidBody& from ) {

	if( !_reloading ) {
		Vector2 pos = from.transform._position;
		pos.x += cos( Math::Radians( from.Forward( ) ) ) * 44;
		pos.y += sin( Math::Radians( from.Forward( ) ) ) * 44;
		CEntMan::GetInstance( ).Add( new CProjectile( pos, from.Forward( ) ) );
		_reloading = true;
	}

	_reloadCounter++;

	if( _reloadCounter >= _reloadTime ) {
		_reloading = false;
		_reloadCounter = 0;
	}

}

void CWepBlaster::Wait( void ) {

	_reloadCounter++;

	if( _reloadCounter >= _reloadTime ) {
		_reloading = false;
		_reloadCounter = 0;
	}

}

void CWepLaser::Fire( CRigidBody& from ) {
	
	t_real focalDistance =  512;

	Vector2 pos = from.transform._position;
	pos.x += cos( Math::Radians( from.Forward( ) ) ) * ( 18 + focalDistance / 2 );
	pos.y += sin( Math::Radians( from.Forward( ) ) ) * ( 18 + focalDistance / 2 );

	if( !_laser ) {
		_laser = new CLaser( pos, focalDistance );
		CEntMan::GetInstance( ).Add( _laser );
	}
	else {
		_laser->Enable( );
		_laser->SetPosition( pos );
		_laser->GetRigidBody( ).transform._angle = from.Forward( );
		_laser->GetRigidBody( ).transform._scale = { 1.0, 1.0 };
	}

}

void CWepLaser::Wait( void ) {
	if( _laser ) _laser->Disable( );
}