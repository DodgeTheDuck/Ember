#pragma once

#include <c_common.h>

class CEntity;

class CEntMan {

	public:
	void Add( CEntity * entity );
	void Kill( CEntity * entity );
	void Tick( void );
	void Draw( void );
	std::vector<CEntity*>& GetList( );
	static CEntMan& GetInstance( );
	private:
	static std::vector<CEntity*> _kill;
	static std::vector<CEntity*> _entities;

};