
#include "c_collision_solver.h"
#include "c_entman.h"
#include "c_entity.h"
#include "c_hull.h"

void CCollisionSolver::Test( void ) {
	
	std::vector<CEntity*> entities = CEntMan::GetInstance( ).GetList( );

	for( t_uint i = 0; i < entities.size( ); i++ ) {

		CEntity * e0 = entities[i];

		for( t_uint j = 0; j < entities.size( ); j++ ) {
		
			CEntity * e1 = entities[j];

			if( i == j ) continue;

			if( e0->GetRigidBody( ).hull && e1->GetRigidBody( ).hull ) {

				CRigidBody& r0 = e0->GetRigidBody( );
				CRigidBody& r1 = e1->GetRigidBody( );

				s_colInfo * info = e0->GetRigidBody( ).hull->Test( &r0, &r1 );

				if( info ) {

					SolveElastic( info->self, info->other );
					e0->OnCollision( info );
					e1->OnCollision( info );

				}

			}


		}
	}

}


void CCollisionSolver::SolveElastic( CRigidBody * c0, CRigidBody * c1 ) {

	Vector2 delta = c0->transform._position - c1->transform._position;
	t_real d = delta.Length( );
	if( d == 0 ) return;
	Vector2 mtd = delta * ( ( ( c0->hull->GetMinDistance( ) + c1->hull->GetMinDistance( ) ) - d ) / d );

	t_real im1 = 1.0 / c0->mass;
	t_real im2 = 1.0 / c1->mass;

	c0->transform._position += mtd * ( im1 / ( im1 + im2 ) );
	c1->transform._position -= mtd * ( im2 / ( im1 + im2 ) );

	Vector2 v = c0->GetVelocity( )- c1->GetVelocity( );
	mtd.Normalise( );
	t_real vn = v.Dot( mtd );

	if( vn > 0.0f ) return;

	t_real restitution = 0.1;

	t_real i = ( -( 1.0 + restitution ) * vn ) / ( im1 + im2 );
	Vector2 impulse = mtd * i;

	c0->Impulse( impulse.Length( ) * im1, Math::Degrees( impulse.Direction( ) ) );
	c1->Impulse( -( impulse.Length( ) * im2 ), Math::Degrees( impulse.Direction( ) ) );

}
