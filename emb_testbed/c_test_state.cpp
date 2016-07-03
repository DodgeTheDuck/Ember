
#include "c_test_state.h"
#include <c_core.h>
#include <c_window.h>
#include <c_image.h>
#include "c_player.h"
#include "c_asteroid.h"
#include <time.h>
#include "c_fire.h"
#include "c_emitter.h"
#include "c_camera.h"
#include <c_spritebank.h>
#include "c_resources.h"
#include <c_emdl.h>
#include <c_shape.h>
#include <c_font.h>
#include "c_collision_solver.h"
#include <c_shader.h>

using namespace EmbCL;

EMBER_ENTRY( new CTestState( ), new CWindow( { 256, 256, WINDOW_W, WINDOW_H }, "Testbed", "TB0" ) );

CCamera * camera;
CFont * font;

t_uint frameCounter;

CCollisionSolver solver;

CTestState::CTestState( void ) : entMan( CEntMan::GetInstance( ) ) {

}

void CTestState::Init( void ) {

	CSpriteBank bank = CSpriteBank::GetInstance( );
	
	EmbR::CreateDevice( EmbCL::SCore::GetInstance( ).WindowManager( )[0]->GetHandle( ) );
	EmbR::Init( );

	bank.Load( PATH_SHIP0 );
	bank.Load( PATH_ASTEROID );
	bank.Load( PATH_PARTICLE );
	bank.Load( PATH_LASER );

	CPlayer * player = new CPlayer( );
	player->SetPosition( Vector2( 256, 256 ) );
	srand( time( NULL ) );

	camera = new CCamera( );
	camera->SetTarget( &player->GetRigidBody( ) );

	entMan.Add( player );
	//entMan.Add( camera );

	SFontInfo fontInfo;
	fontInfo.bmpPath = "RESOURCE/font/gui.png";
	fontInfo.cols = 16;
	fontInfo.rows = 16;
	fontInfo.charWidth = 14;
	fontInfo.charHeight = 16;

	font = new CFont( fontInfo );

	for( t_uint i = 0; i < 8; i++ ) {
		CAsteroid * asteroid = new CAsteroid( { (t_real) ( rand( ) % 1600 ), (t_real) ( rand( ) % 1024 ) }  );
		asteroid->GetRigidBody( ).Impulse( 0.1, rand( ) % 360 );
		entMan.Add( asteroid );
	}

}

void CTestState::Tick( void ) {

	frameCounter++;

	/*t_uint chance = rand( ) % 500;

	if( chance <= 3 ) {
		if( chance == 0 ) {
			CAsteroid * asteroid = new CAsteroid( { (t_real)(rand( ) % 1600), -16 } );
			asteroid->GetRigidBody( ).Impulse( 0.1, 6 + rand( ) % 60 );
			entMan.Add( asteroid );
		}
		if( chance == 1 ) {
			CAsteroid * asteroid = new CAsteroid( { (t_real) ( rand( ) % 1600), 1040 } );
			asteroid->GetRigidBody( ).Impulse( 0.1, 240 + rand( ) % 60 );
			entMan.Add( asteroid );
		}
	}*/

	if( frameCounter >= SCore::GetInstance( ).GetFPS( ) ) {
		std::cout << "Entities: " << entMan.GetList( ).size( ) << std::endl;
		frameCounter = 0;
	}

	entMan.Tick( );

	solver.Test( );

}

void CTestState::Draw( void ) {
	EmbR::PushTransform( camera->GetRigidBody( ).transform );
	EmbR::GetPostShader( ).Enable( );
	EmbR::GetPostShader( ).UniformVec2( "s_effect_pixelate.sample_size", 4, 4 ); //floor( 16 * ( pow( camera->GetRigidBody( ).transform._scale.x, 2 ) ) ), floor( 16 * ( pow( camera->GetRigidBody( ).transform._scale.y, 2 ) ) ) );
	EmbR::GetPostShader( ).UniformFloat( "s_effect_pixelate.strength", 1.0 );
	EmbR::GetPostShader( ).Disable( );
	entMan.Draw( );
	//font->DrawString( 32, 32, "Shield", 2.0 );
	//font->DrawString( 32, 64, "Hull", 2.0 );
	EmbR::PopTransform( );
}