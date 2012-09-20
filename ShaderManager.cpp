#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <gl/glew.h>
#include <gl/gl.h>		
#include <fstream>
#include <iostream>
#include "ShaderManager.h"
#include "VertexBuffer.h"

ShaderManager::ShaderManager()
{
	currentProgramId = 0;
}

ShaderManager::~ShaderManager()
{
	cleanupShaders();
}

void ShaderManager::cleanupShaders()
{
	GLuint attachedShaders[ 10 ];
	GLsizei count;
	std::tr1::unordered_map< std::string, GLuint >::iterator itr;
	for( itr = shaders.begin(); itr != shaders.end(); ++itr )
	{
		glGetAttachedShaders( itr->second, 10, &count, attachedShaders );
		glDeleteProgram( itr->second );
		for( int i = 0; i < count; i++ )
		{
			glDeleteShader( attachedShaders[ i ] );
		}
	}
}

bool ShaderManager::loadShaders( const char *programName, const char *vertexProgram, const char *fragmentProgram )
{
	std::tr1::unordered_map< std::string, GLuint >::const_iterator itr
		= shaders.find( programName );

	if( itr != shaders.end() )
		return false;

	GLuint pId = glCreateProgram();
	if( pId == 0 )
		return false;

	GLuint vId = glCreateShader( GL_VERTEX_SHADER );
	if( vId == 0 )
	{
		glDeleteProgram( pId );
		return false;
	}

	GLuint fId = glCreateShader( GL_FRAGMENT_SHADER );
	if( fId == 0 )
	{
		glDeleteShader( vId );
		glDeleteProgram( pId );
		return false;
	}

	const GLchar *p[1];
	GLint lengths[1];
	
	p[ 0 ] = vertexProgram;
	lengths[ 0 ] = strlen( vertexProgram );
	glShaderSource( vId, 1, p, lengths );
	glCompileShader( vId );

	GLint success;
	glGetShaderiv( vId, GL_COMPILE_STATUS, &success );
	if( success == 0 )
	{
		GLchar error[ 65535 ];
		glGetShaderInfoLog( vId, sizeof( error ), NULL, error );
		std::cerr << "Error compiling Vertex Shader:" << std::endl;
		std::cerr << error << std::endl;

		glDeleteShader( vId );
		glDeleteShader( fId );
		glDeleteProgram( pId );
		return false;
	}

	p[ 0 ] = fragmentProgram;
	lengths[ 0 ] = strlen( fragmentProgram );
	glShaderSource( fId, 1, p, lengths );
	glCompileShader( fId );

	glGetShaderiv( fId, GL_COMPILE_STATUS, &success );
	if( success == 0 )
	{
		GLchar error[ 65535 ];
		glGetShaderInfoLog( fId, sizeof( error ), NULL, error );
		std::cerr << "Error compiling Fragment Shader:" << std::endl;
		std::cerr << error << std::endl;

		glDeleteShader( vId );
		glDeleteShader( fId );
		glDeleteProgram( pId );
		return false;
	}

	glAttachShader( pId, vId );
	glAttachShader( pId, fId );
	glLinkProgram( pId );
	glGetProgramiv( pId, GL_LINK_STATUS, &success );
	if( success == 0 ){
		GLchar error[ 65535 ];
		glGetProgramInfoLog( pId, sizeof( error ), NULL, error );
		std::cerr << "Error linking Shader Program:" << std::endl;
		std::cerr << error << std::endl;

		glDeleteShader( vId );
		glDeleteShader( fId );
		glDeleteProgram( pId );
		return false;
	}

	shaders[ programName ] = pId;
	currentProgramId = pId;

	return true;
}

bool ShaderManager::loadShaderFile( const char *fileName, std::string &src )
{
	std::ifstream f;
	f.open( fileName );
	if( !f.is_open() || !f.good() )
		return false;

	src.clear();

	std::string line;
	while( !f.eof() )
	{
		std::getline( f, line );

		if( f.bad() )
		{
			f.close();
			return false;
		}

		line += '\n';
		src += line;
	}

	f.close();
	return true;
}

bool ShaderManager::loadShaderFiles( const char *programName, const char *vertexProgramFile, const char *fragmentProgramFile )
{
	std::tr1::unordered_map< std::string, GLuint >::const_iterator itr
		= shaders.find( programName );
	if( itr != shaders.end() )
		return false;

	std::string vertexSrc;
	std::string fragmentSrc;

	if( !loadShaderFile( vertexProgramFile, vertexSrc ) )
		return false;
	if( !loadShaderFile( fragmentProgramFile, fragmentSrc ) )
		return false;

	return loadShaders( programName, vertexSrc.c_str(), fragmentSrc.c_str() );
}

bool ShaderManager::useProgram( const char *programName )
{
	std::tr1::unordered_map< std::string, GLuint >::const_iterator itr
		= shaders.find( programName );
	if( itr == shaders.end() )
		return false;
	
	glUseProgram( itr->second );
	return true;
}

