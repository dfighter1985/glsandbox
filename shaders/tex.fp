#version 330

uniform sampler2D sampler;

smooth in vec2 texCoords;

out vec4 fragmentColor;

void main( void )
{
	fragmentColor = texture( sampler, texCoords );
}
