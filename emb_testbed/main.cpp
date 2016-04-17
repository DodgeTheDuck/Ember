
#include "c_test_stack.h"
#include <c_core.h>
#include <stack>

using namespace EmbCL;

int main( ) {

	EmbCL::S_Core& core = S_Core::GetInstance( );

	core.StateMachine( ).Push( CTestStack( ) );

	core.Init( );
	core.Run( );
	core.Shutdown( );

	system( "PAUSE" );

}