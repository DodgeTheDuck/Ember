#pragma once

#include <c_common.h>
#include <c_state.h>
#include "c_entity.h"
#include "c_entman.h"

using namespace EmbCL;
using namespace Emb;

class CTestState : public CState {

	public:
	CTestState( void );
	virtual void Init( void );
	virtual void Tick( void );
	virtual void Draw( void );

	private:
	CEntMan& entMan;

};