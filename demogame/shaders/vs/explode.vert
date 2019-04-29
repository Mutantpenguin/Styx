out VS_OUT
{
	vec2 UV;
};

void main()
{
	gl_Position = vec4( position, 1 );

	UV = uv0;
}
