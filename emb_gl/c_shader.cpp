
#include "c_shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL\glew.h>

void CShader::LoadFromFile( const char * path, SHADER_TYPE type ) {

	std::ifstream t( path );
	std::stringstream buffer;
	buffer << t.rdbuf( );

	LoadFromString( buffer.str( ), type );

	t.close( );

}

void CShader::LoadFromString( std::string shader, SHADER_TYPE type ) {

	const char * source = shader.c_str( );
	const int length = shader.length( );

	if( !_program ) _program = glCreateProgramObjectARB( );

	switch( type ) {

		case SHADER_FRAGMENT:
			_fragment = glCreateShader( GL_FRAGMENT_SHADER );
			glShaderSource( _fragment, 1, &source, &length );
			glCompileShader( _fragment );
			break;
		case SHADER_VERTEX:
			_vertex = glCreateShader( GL_VERTEX_SHADER );
			glShaderSource( _vertex, 1, &source, &length );
			glCompileShader( _vertex );
			break;
		default:
			return;
	}

}

void CShader::Link( void ) {

	glAttachObjectARB( _program, _fragment );
	glAttachObjectARB( _program, _vertex );

	GLint compiled;

	glGetObjectParameterivARB( _fragment, GL_COMPILE_STATUS, &compiled );

	if( !compiled ) {

		GLint blen = 0;
		GLsizei slen = 0;

		glGetShaderiv( _fragment, GL_INFO_LOG_LENGTH, &blen );

		if( blen > 1 ) {
			GLchar* compiler_log = (GLchar*) malloc( blen );
			glGetInfoLogARB( _fragment, blen, &slen, compiler_log );
			std::cout << std::string( "compiler_log:\n" ) + std::string( compiler_log );
			free( compiler_log );
		}

	}

	glGetObjectParameterivARB( _vertex, GL_COMPILE_STATUS, &compiled );

	if( !compiled ) {

		GLint blen = 0;
		GLsizei slen = 0;

		glGetShaderiv( _vertex, GL_INFO_LOG_LENGTH, &blen );

		if( blen > 1 ) {
			GLchar* compiler_log = (GLchar*) malloc( blen );
			glGetInfoLogARB( _vertex, blen, &slen, compiler_log );
			std::cout << std::string( "compiler_log:\n" ) + std::string( compiler_log );
			free( compiler_log );
		}

	}

	glLinkProgram( _program );
	glDeleteObjectARB( _fragment );
	glDeleteObjectARB( _vertex );
}


void CShader::UniformFloat( const char * varName, float f ) {
	GLint id = glGetUniformLocation( _program, varName );
	glUniform1f( id, f );
}

void CShader::UniformVec4( const char * varName, float data[4] ) { 
	GLint id = glGetUniformLocation( _program, varName );
	glUniform4f( id, data[0], data[1], data[2], data[3] );
}

void CShader::UniformVec3( const char * varName, float data[3] ) {
	GLint id = glGetUniformLocation( _program, varName );
	glUniform3f( id, data[0], data[1], data[2] );
}

void CShader::UniformVec2( const char * varName, float data[2] ) {
	GLint id = glGetUniformLocation( _program, varName );
	glUniform2f( id, data[0], data[1] );
}

void CShader::UniformVec2( const char * varName, float d0, float d1 ) {
	GLint id = glGetUniformLocation( _program, varName );
	glUniform2f( id, d0, d1 );
}

void CShader::UniformVec4( const char * varName, t_color4_r data ) {
	GLint id = glGetUniformLocation( _program, varName );
	glUniform4f( id, (GLfloat)data.r, (GLfloat) data.g, (GLfloat) data.b, (GLfloat) data.a );
}

/*void CShader::UniformMat4x4( const char * varName, Mat4x4 &mat ) {
	GLint id = glGetUniformLocation( _program, varName );
	glUniformMatrix4fv( id, 1, GL_FALSE, &mat.data[0] );
}*/

void CShader::UniformUInt( const char * varName, t_uint sampler ) {
	GLint id = glGetUniformLocation( _program, varName );
	glUniform1ui( id, sampler );
}

void CShader::UniformInt( const char * varName, t_int32 sampler ) {
	GLint id = glGetUniformLocation( _program, varName );
	glUniform1i( id, sampler );
}

void CShader::Enable( void ) {
	glUseProgramObjectARB( _program );
}

void CShader::Disable( void ) {
	glUseProgramObjectARB( 0 );
}

