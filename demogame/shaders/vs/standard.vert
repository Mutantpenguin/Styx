out vec2 UV;

void main()
{
	gl_Position = modelViewProjectionMatrix * vec4( position, 1 );

	UV = uv0;
}
