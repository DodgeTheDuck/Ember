#pragma once

#include "c_common.h"

namespace EmbCL {

	class S_Core : public ISingleton {

		public:

		S_Core( void );
		void Init( void );
		void Run( void );
		void Shutdown( void );

		CStackDY<IState>& StateMachine( void );

		static S_Core& GetInstance( );

		private:

		CStackDY<IState> _states;

		public:
		S_Core( const S_Core& ) = delete;
		void operator=( const S_Core& ) = delete;

	};

}