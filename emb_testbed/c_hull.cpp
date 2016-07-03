
#include <c_wrapper.h>
#include "c_hull.h"
#include "c_rigidBody.h"

s_colInfo * CHull::Test( CRigidBody * self, CRigidBody * other ) {
	return NULL;
}

t_rect_r CHull::GetBounds( void ) {
	return _bounds;
}

void CHull::SetTransform( Transform2D * transform ) {
	_transform = transform;
}

Transform2D CHull::GetTransform( void ) {
	return *_transform;
}

void CHull::Draw( void ) {

}

t_real CHull::GetMinDistance( void ) {
	return 0;
}

e_hullType CHull::GetType( void ) {
	return _type;
}

s_colInfo * CHullCircle::Test( CRigidBody * self, CRigidBody * other ) {

	//if( self->GetTag( ) == other->GetTag( ) ) return NULL;

	Vector2 centre0 = _transform->_position;
	Vector2 centre1 = other->transform._position;
	t_real distance = Math::Distance( centre0, centre1 );

	switch( other->hull->GetType( ) ) {
		case HULL_CIRCLE:
			if( _radius + other->hull->GetMinDistance( ) >= distance ) {
				s_colInfo * c = new s_colInfo( );
				c->other = other;
				c->self = self;
				return c;
			}
			break;
	}

	return NULL;
}

void CHullCircle::Draw( void ) {
	EmbR::DrawCircle( _transform->_position, _radius );
}

t_rect_r CHullCircle::GetBounds( void ) {
	return _bounds;
}

t_real CHullCircle::GetMinDistance( void ) {
	return _radius;
}