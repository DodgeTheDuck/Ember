#pragma once

#include <c_defs.h>

class CShader {

	public:
	enum SHADER_TYPE {
		SHADER_VERTEX,
		SHADER_FRAGMENT
	};

	void LoadFromFile( const char * path, SHADER_TYPE type );
	void LoadFromString( std::string shader, SHADER_TYPE type );
	void Link( void );

	//void UniformMat4x4( const char * varName, Mat4x4 &mat );
	void UniformUInt( const char * varName, t_uint value );
	void UniformInt( const char * varName, t_int32 value );
	void UniformFloat( const char * varName, float value );
	void UniformVec4( const char * varName, float data[4] );
	void UniformVec4( const char * varName, t_color4_r data );
	void UniformVec2( const char * varName, float data[2] );
	void UniformVec2( const char * varName, float d0, float d1 );
	void UniformVec3( const char * varName, float data[3] );

	void Enable( void );
	void Disable( void );

	private:
	t_uint _program = 0;
	t_uint _vertex = 0;
	t_uint _fragment = 0;

};
