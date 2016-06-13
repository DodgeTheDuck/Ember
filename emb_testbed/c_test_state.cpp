
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


using namespace EmbCL;

EMBER_ENTRY( new CTestState( ), new CWindow( { 256, 256, 1600, 1024 }, "Testbed", "TB0" ) );

CCamera * camera;
CFont * font;

CTestState::CTestState( void ) : entMan( CEntMan::GetInstance( ) ) {

}

void CTestState::Init( void ) {

	CSpriteBank bank = CSpriteBank::GetInstance( );
	
	EmbR::CreateDevice( EmbCL::SCore::GetInstance( ).WindowManager( )[0]->GetHandle( ) );
	EmbR::Init( );

	bank.Load( PATH_SHIP0 );
	bank.Load( PATH_ASTEROID );
	bank.Load( PATH_PARTICLE );

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

}

void CTestState::Tick( void ) {

	t_uint chance = rand( ) % 200;

	if( chance <= 3 ) {
		if( chance == 0 ) {
			CAsteroid * asteroid = new CAsteroid( { (t_real)(rand( ) % 1600), -16 } );
			asteroid->GetRigidBody( ).Impulse( rand( ) % 5 + 1, 60 + rand( ) % 60 );
			entMan.Add( asteroid );
		}
		if( chance == 1 ) {
			CAsteroid * asteroid = new CAsteroid( { (t_real) ( rand( ) % 1600), 1040 } );
			asteroid->GetRigidBody( ).Impulse( rand( ) % 5 + 1, 240 + rand( ) % 60 );
			entMan.Add( asteroid );
		}
	}

	entMan.Tick( );
}

void CTestState::Draw( void ) {
	EmbR::PushTransform( camera->GetRigidBody( ).transform );
	entMan.Draw( );
	font->DrawString( 32, 32, "abcdefghijklmnopqrstuvwxyz" );
	EmbR::PopTransform( );
}