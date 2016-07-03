#pragma once

#include <c_common.h>

class CRigidBody;

class CCollisionSolver {

	public:

	void Test( void );
	void SolveElastic( CRigidBody * r0, CRigidBody * r1 );

};