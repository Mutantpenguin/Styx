out VS_OUT
{
	vec2 UV;
};

void main()
{
	gl_Position = modelViewProjectionMatrix * vec4( position, 1 );

	UV = texcoord0;
}
