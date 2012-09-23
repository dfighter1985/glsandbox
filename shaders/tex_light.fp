#version 330

uniform sampler2D sampler;

smooth in vec2 texCoords;
smooth in float luminosity;

out vec4 fragmentColor;


void main( void )
{
	float ambience = 0.3;
	vec4 diffcolor = vec4( 0.3, 0.0, 0.0, 0.3 );
	vec4 texel     = texture( sampler, texCoords );
	fragmentColor  = luminosity * ( diffcolor * texel ) + ambience  * texel;
}
