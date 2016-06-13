
#include "c_shield.h"
#include "c_hull.h"
#include "c_entman.h"
#include "c_emitter.h"

CShield::CShield( void ) {
	Init( );
}

void CShield::Init( void ) {
	_rigidBody.hull = new CHullCircle( 64, &_rigidBody.transform );
	_rigidBody.mass = 500;
	_rigidBody.SetTag( 1 );
}

void CShield::Tick( void ) {
	
}

void CShield::Draw( void ) {

	EmbR::DrawCircle( _rigidBody.transform._position, 64 );

}

void CShield::OnCollision( s_colInfo * colInfo ) {

}