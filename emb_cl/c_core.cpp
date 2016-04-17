
#include "c_core.h"
#include "c_state.h"

namespace EmbCL {

	S_Core::S_Core( void ) { }

	void S_Core::Init( void ) {

	}

	void S_Core::Run( void ) {

	}

	void S_Core::Shutdown( void ) {

	}

	CStackDY<IState>& S_Core::StateMachine( void ) {
		return _states;
	}

	S_Core& S_Core::GetInstance( void ) {
		static S_Core instance;
		return instance;
	}

}