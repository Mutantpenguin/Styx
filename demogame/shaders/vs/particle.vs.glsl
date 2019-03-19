void main()
{
	gl_Position = modelViewMatrix * vec4( position, 1 );
}
