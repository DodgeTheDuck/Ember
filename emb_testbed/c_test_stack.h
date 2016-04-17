#pragma once

#include <c_common.h>
#include <c_state.h>
#include <stack>

using namespace EmbCL;

class CTestStack : public IState {

	public:

	CTestStack( void ) {

		CStopwatch timer;

		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

		std::cout << "My Stack Construction" << std::endl;
		timer.Start( );
		CStackDY<int> stack;
		timer.Stop( );
		std::cout << ">> " << timer.Read( ) << " Ms" << std::endl;
		timer.Reset( );

		std::cout << "My Stack Push" << std::endl;
		timer.Start( );
		for( t_uint i = 0; i < 1025; i++ ) {
			stack.Push( int( i ) );
		}
		timer.Stop( );
		std::cout << ">> " << timer.Read( ) << " Ms" << std::endl;
		timer.Reset( );

		std::cout << "My Stack Top" << std::endl;
		timer.Start( );
		for( t_uint i = 0; i < 1024; i++ ) {
			int j = stack.Top( );
		}
		timer.Stop( );
		std::cout << ">> " << timer.Read( ) << " Ms" << std::endl;
		timer.Reset( );

		std::cout << "My Stack Pop" << std::endl;
		timer.Start( );
		for( t_uint i = 0; i < 512; i++ ) {
			stack.Pop( );
		}
		timer.Stop( );
		std::cout << ">> " << timer.Read( ) << " Ms" << std::endl;
		timer.Reset( );

		std::cout << "My Stack Mem" << std::endl;
		std::cout << ">> " << sizeof( CStackDY<int> ) + stack.GetTotalPoolSize( ) << " Bytes" << std::endl;

		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

		std::cout << "STD Stack Construction" << std::endl;
		timer.Start( );
		std::stack<int> std_stack;
		timer.Stop( );
		std::cout << ">> " << timer.Read( ) << " Ms" << std::endl;
		timer.Reset( );

		std::cout << "STD Stack Push" << std::endl;
		timer.Start( );
		for( t_uint i = 0; i < 1024; i++ ) {
			std_stack.push( i );
		}
		timer.Stop( );
		std::cout << ">> " << timer.Read( ) << " Ms" << std::endl;
		timer.Reset( );

		std::cout << "STD Stack Top" << std::endl;
		timer.Start( );
		for( t_uint i = 0; i < 1024; i++ ) {
			int j = std_stack.top( );
		}
		timer.Stop( );
		std::cout << ">> " << timer.Read( ) << " Ms" << std::endl;
		timer.Reset( );

		std::cout << "STD Stack Pop" << std::endl;
		timer.Start( );
		for( t_uint i = 0; i < 512; i++ ) {
			std_stack.pop( );
		}
		timer.Stop( );
		std::cout << ">> " << timer.Read( ) << " Ms" << std::endl;
		timer.Reset( );

		std::cout << "STD Stack Mem" << std::endl;
		std::cout << ">> " << sizeof( std::stack<int> ) + std_stack.size( ) * sizeof( int ) << " Bytes" << std::endl;

	}

	virtual void Tick( void ) { };

	virtual void Draw( void ) { };

};