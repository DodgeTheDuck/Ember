
#include "c_entman.h"
#include <algorithm>
#include "c_entity.h"

std::vector<CEntity*> CEntMan::_entities;
std::vector<CEntity*> CEntMan::_kill;

void CEntMan::Add( CEntity * entity ) {
	_entities.push_back( entity );
}

void CEntMan::Tick( void ) {

	for( t_uint i = 0; i < _kill.size( ); i++ ) {
		CEntity * ent = _kill[i];
		_entities.erase( std::remove( _entities.begin( ), _entities.end( ),  ent ), _entities.end( ) );
		delete ent;
	}

	_kill.clear( );

	for( t_uint i = 0; i < _entities.size( ); i++ ) {
		CEntity * entity = _entities[i];
		if( entity->IsEnabled( ) ) entity->Tick( );
	}

}

void CEntMan::Kill( CEntity * entity ) {	
	_kill.push_back( entity );
}

void CEntMan::Draw( void ) {
	for( t_uint i = 0; i < _entities.size( ); i++ ) {
		CEntity * entity = _entities[i];
		if( entity->IsEnabled( ) ) entity->Draw( );
	}
}

std::vector<CEntity*>& CEntMan::GetList( void ) {
	return _entities;
}

CEntMan& CEntMan::GetInstance( void ) {
	static CEntMan entMan;
	return entMan;
}