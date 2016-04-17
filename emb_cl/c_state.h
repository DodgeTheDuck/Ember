#pragma once

namespace EmbCL {

	class IState {

		public:

		virtual void Tick( void ) = 0;
		virtual void Draw( void ) = 0;

		private:

	};

}
