#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <string>
#include <unordered_map>

class ShaderManager
{

public:
	ShaderManager();
	~ShaderManager();
	void cleanupShaders();
	bool loadShaders( const char *programName, const char *vertexProgram, const char *fragmentProgram );
	bool loadShaderFile( const char *fileName, std::string &src );
	bool loadShaderFiles( const char *programName, const char *vertexProgramFile, const char *fragmentProgramFile );
	bool useProgram( const char *programName );

private:
	std::tr1::unordered_map< std::string, unsigned int > shaders;
};

#endif

