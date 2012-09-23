#version 330

uniform sampler2D sampler;

smooth in vec2 texCoords;
smooth in float luminosity;

out vec4 fragmentColor;


void main( void )
{
	fragmentColor = luminosity * texture( sampler, texCoords );
}
