
#include "c_particle.h"
#include <c_image.h>
#include "c_entman.h"

CParticle::CParticle( const SPartInfo& info ) : CEntity( ) {

	_life = Math::RandomRange( info.minLifespan, info.maxLifespan );
	_grav = Math::RandomRange( info.minGrav, info.maxGrav );
	_gravDir = Math::RandomRange( info.minGravDir, info.maxGravDir );
	_rigidBody.transform._scale = Math::RandomRange( info.minScale, info.maxScale );

	_span = _life;

	_sprite = CSpriteBank::GetInstance( ).Get( SPRH_PARTICLE );

	_start = {
		info.startColor.r + Math::RandomRange( -info.startVariance.r, info.startVariance.r ),
		info.startColor.g + Math::RandomRange( -info.startVariance.g, info.startVariance.g ),
		info.startColor.b + Math::RandomRange( -info.startVariance.b, info.startVariance.b ),
		info.startColor.a + Math::RandomRange( -info.startVariance.a, info.startVariance.a )
	};

	_end = {
		info.endColor.r + Math::RandomRange( -info.endVariance.r, info.endVariance.r ),
		info.endColor.g + Math::RandomRange( -info.endVariance.g, info.endVariance.g ),
		info.endColor.b + Math::RandomRange( -info.endVariance.b, info.endVariance.b ),
		info.endColor.a + Math::RandomRange( -info.endVariance.a, info.endVariance.a )
	};

	_sprite->SetBlendMode( info.mode );

}

void CParticle::Init( void ) {

}

void CParticle::Tick( void ) {

	if( _life <= 0 ) CEntMan::GetInstance( ).Kill( this );
	_life--;
	
	_sprite->SetColor(
		Math::Interp1( _span, _life, _end.r, _start.r ),
		Math::Interp1( _span, _life, _end.g, _start.g ),
		Math::Interp1( _span, _life, _end.b, _start.b ),
		Math::Interp1( _span, _life, _end.a, _start.a )
	);

	_rigidBody.Impulse( _grav, _gravDir );

	CEntity::Tick( );
}

void CParticle::Draw( void ) {
	CEntity::Draw( );
}