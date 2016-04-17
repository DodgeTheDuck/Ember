#pragma once

#include <c_common.h>
#include <c_state.h>

using namespace EmbCL;

class CTestState : public IState {

	public:
	virtual void Tick( void );
	virtual void Draw( void );

};