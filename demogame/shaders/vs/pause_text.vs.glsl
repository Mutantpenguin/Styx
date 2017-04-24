varying vec4 textureCoords;

out vec2 UVfg;

void main()
{
	const uint width = 512;
	const uint height = 128;

	vec2 rasterPosition = vec2( Screen.width / 2.0 + width * ( vertex.x + 0.5 ),
								Screen.height / 2.0 + height * ( vertex.y + 0.5 ) );

	textureCoords = vec4( vertex.x + 0.5, vertex.y + 0.5, 0.0, 0.0 );

	//gl_Position = vec4( vertex.xy, 0.0, 1.0 );
	gl_Position = vec4(
               2.0 * rasterPosition.x / Screen.width - 1.0,
               2.0 * rasterPosition.y / Screen.height - 1.0,
               -1.0, // near plane
               1.0 // all coordinates are divided by this coordinate
               );

	UVfg = texcoord;
}
