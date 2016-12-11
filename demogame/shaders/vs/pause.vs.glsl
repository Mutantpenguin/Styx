out vec2 UV;

void main()
{
	gl_Position = vec4( vertex.xy, 0.0, 1.0 );

	UV = ( textureMatrix * vec3( texcoord, 1 ) ).st;
}
