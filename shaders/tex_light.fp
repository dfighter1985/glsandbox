#version 330

uniform sampler2D sampler;

smooth in vec2 texCoords;
smooth in float luminosity;
smooth in float luminosity2;

out vec4 fragmentColor;


void main( void )
{
	float ambience  = 0.3;
	vec4 diffcolor  = vec4( 0.3, 0.0, 0.0, 0.3 );
	vec4 diffcolor2 = vec4( 0.0, 0.0, 0.3, 0.3 );
	vec4 texel      = texture( sampler, texCoords );
	fragmentColor   = luminosity * diffcolor * texel + luminosity2 * diffcolor2 * texel + ambience * texel;
}
