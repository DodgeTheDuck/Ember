
#include "c_rigidBody.h"
#include "c_entity.h"
#include "c_entman.h"
#include "c_hull.h"
#include <vector>

CRigidBody::CRigidBody( void ) {
	_angularAcceleration = 0;
	_angularVelocity = 0;
	hull = NULL;
}

void CRigidBody::Tick( void ) {

	_velocity += _acceleration;
	transform._position += _velocity;
	_acceleration = Vector2( 0, 0 );

	_angularVelocity += _angularAcceleration;
	transform._angle += _angularVelocity;
	_angularAcceleration = 0;

	if( hull ) {

		std::vector<CEntity*>& others = CEntMan::GetInstance( ).GetList( );

		for( t_uint i = 0; i < others.size( ); i++ ) {

			if( &others[i]->GetRigidBody( ) == this ) continue;
			if( others[i]->GetRigidBody( ).hull == NULL ) continue;

			s_colInfo * info = hull->Test( this, &others[i]->GetRigidBody( ) );

			if( info ) {

				SolveElastic( info->other );
				others[i]->OnCollision( info );

			}

		}

	}

}

t_real CRigidBody::Forward( void ) {
	return transform._angle;
}


t_tag CRigidBody::GetTag( void ) {
	return _tag;
}

void CRigidBody::SetTag( t_tag tag ) {
	_tag = tag;
}

void CRigidBody::Impulse( t_real force, t_real direction, Vector2 offset ) {

	t_real xCoeff = abs( 1.0 / ( 1.0 / offset.x ) );
	t_real yCoeff = abs( 1.0 / ( 1.0 / offset.y ) );

	_acceleration.x += cos( Math::Radians( direction ) ) * force * ( 1.0 - xCoeff );
	_acceleration.y += sin( Math::Radians( direction ) ) * force * ( 1.0 - yCoeff );

	Vector2 angularCoeff = { xCoeff, yCoeff };
	angularCoeff.Normalise( );
	t_real angularLength = angularCoeff.Length( );

	if( offset.x > 0 )
		_angularAcceleration += force * angularCoeff.Length( );
	else if( offset.x < 0 )
		_angularAcceleration -= force * angularCoeff.Length( );

}

void CRigidBody::SolveElastic( CRigidBody * other ) {

	Vector2 delta = transform._position - other->transform._position;
	t_real d = delta.Length( );
	if( d == 0 ) return;
	Vector2 mtd = delta * ( ( ( hull->GetMinDistance( ) + other->hull->GetMinDistance( ) ) - d ) / d );

	t_real im1 = 1.0 / mass;
	t_real im2 = 1.0 / other->mass;

	transform._position += mtd * ( im1 / ( im1 + im2 ) );
	other->transform._position -= mtd * ( im2 / ( im1 + im2 ) );

	Vector2 v = _velocity - other->GetVelocity( );
	mtd.Normalise( );
	t_real vn = v.Dot( mtd );

	if( vn > 0.0f ) return;

	t_real restitution = 0.4;

	t_real i = ( -( 1.0 + restitution ) * vn ) / ( im1 + im2 );
	Vector2 impulse = mtd * i;

	Impulse( impulse.Length( ) * im1, Math::Degrees( impulse.Direction( ) ) );
	other->Impulse( -( impulse.Length( ) * im2 ), Math::Degrees( impulse.Direction( ) ) );

}

Vector2 CRigidBody::GetVelocity( void ) {
	return _velocity;
}