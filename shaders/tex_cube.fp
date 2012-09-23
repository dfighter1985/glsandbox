#version 330

uniform samplerCube sampler;

smooth in vec3 texCoords;

out vec4 fragmentColor;

void main( void )
{
	fragmentColor = texture( sampler, texCoords );
}
