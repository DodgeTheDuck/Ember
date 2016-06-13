#pragma once

#include <c_common.h>

class CRigidBody;

enum e_hullType {
	HULL_CIRCLE
};

struct s_colInfo {
	CRigidBody * self;
	CRigidBody * other;
};

class CHull {

	public:
	CHull( void ) { };
	CHull( Transform2D * transform ) : _transform( transform ) { };
	virtual s_colInfo * Test( CRigidBody * self, CRigidBody * other );
	virtual void SetTransform( Transform2D * transform );
	virtual Transform2D GetTransform( void );
	virtual t_rect_r GetBounds( void );
	virtual void Draw( void );
	e_hullType GetType( void );
	virtual t_real GetMinDistance( void );

	protected:

	

	t_rect_r _bounds;
	Transform2D * _transform;
	e_hullType _type;

};

class CHullCircle : public CHull {

	public:
	CHullCircle( t_real radius = 0 ) : _radius( radius ) { _type = HULL_CIRCLE; };
	CHullCircle( t_real radius, Transform2D * transform ) : _radius( radius ), CHull( transform ) { _type = HULL_CIRCLE; };
	virtual s_colInfo * Test( CRigidBody * self, CRigidBody * other );
	virtual t_rect_r GetBounds( void );
	virtual void Draw( void );
	virtual t_real GetMinDistance( void );

	private:
	t_real _radius;

};