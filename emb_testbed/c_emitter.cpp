
#include "c_emitter.h"
#include "c_entman.h"

CEmitter::CEmitter( const Vector2& pos, const SEmitInfo& einfo, const SPartInfo& pinfo ) : CEntity( ) {
	_einfo = einfo;
	_pinfo = pinfo;
	_life = einfo.lifespan;
	SetPosition( pos );
	_enabled = true;
}

void CEmitter::Init( void ) {

}

void CEmitter::Tick( void ) {

	if( _enabled ) {

		_intervalCount++;

		if( _intervalCount >= _einfo.interval ) {

			switch( _einfo.type ) {

				case EMIT_STREAM :
					_Emit( );
					break;
				case EMIT_BURST :
					for( t_uint i = 0; i < _einfo.count; i++ ) {
						_Emit( );
					}
					break;
				case EMIT_LIGHTNING :
					t_real distance = Math::Distance( _rigidBody.transform._position, _einfo.target );
					if( distance == 0 ) break;
					t_real direction = Math::Angle( _rigidBody.transform._position, _einfo.target );
					t_real lines = rand( ) % (int) ( distance / 32 ) + 2;
					t_real lineLength = distance / lines;

					Vector2 from = _rigidBody.transform._position;

					for( t_uint i = 0; i < lines; i++ ) {

						t_real randDir = direction + Math::RandomRange( -0.8, 0.8 );
						
						Vector2 to;
						if( i == lines - 1 ) {
							to = _einfo.target;
						} else {
							to.x = from.x + cos( randDir ) * lineLength;
							to.y = from.y + sin( randDir ) * lineLength;
						}
						t_real partInterval = lineLength / _einfo.count;

						for( t_uint j = 0; j < lineLength; j += partInterval ) {
							_Emit( 
								Vector2(
									Math::Interp1( lineLength, j, to.x, from.x ),
									Math::Interp1( lineLength, j, to.y, from.y )
								) 
							);
						}

						t_real nextOffset = rand( ) % 4 + 6;

						from = Vector2(
							Math::Interp1( 10, nextOffset, from.x, to.x ),
							Math::Interp1( 10, nextOffset, from.y, to.y )
						);

					}

					break;

			}

		}
	}


	if( _einfo.lifespan > 0 ) {

		_life--;

		if( _life <= 0 ) {
			CEntMan::GetInstance( ).Kill( this );
			return;
		}

	}

	CEntity::Tick( );

}

void CEmitter::SetDirection( t_real direction ) {
	_einfo.direction = direction;
}

void CEmitter::Enable( void ) {
	_enabled = true;
}

void CEmitter::Disable( void ) {
	_enabled = false;
}

void CEmitter::Draw( void ) {
	CEntity::Draw( );
}

void CEmitter::_Emit( void ) {
	CParticle * p = new CParticle( _pinfo );
	t_real dir = _einfo.direction + ( ( rand( ) % (int) _einfo.spread ) - _einfo.spread / 2 );
	p->SetPosition( _rigidBody.transform._position );
	p->GetRigidBody( ).Impulse( Math::RandomRange( _einfo.minSpeed, _einfo.maxSpeed ), dir );
	CEntMan::GetInstance( ).Add( p );
	_intervalCount = 0;
}

void CEmitter::_Emit( Vector2 from ) {
	CParticle * p = new CParticle( _pinfo );
	t_real dir = 0;
	if( _einfo.spread != 0 ) t_real dir = _einfo.direction + ( ( rand( ) % (int) _einfo.spread ) - _einfo.spread / 2 );
	p->SetPosition( from );
	p->GetRigidBody( ).Impulse( Math::RandomRange( _einfo.minSpeed, _einfo.maxSpeed ), dir );
	CEntMan::GetInstance( ).Add( p );
	_intervalCount = 0;
}