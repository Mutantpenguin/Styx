out vec2 UV;

void main()
{
	gl_Position = modelViewProjectionMatrix * vec4( vertex, 1 );

	UV = ( textureMatrix * vec3( texcoord, 1 ) ).st;
}
