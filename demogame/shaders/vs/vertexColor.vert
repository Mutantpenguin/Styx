out vec3 vertexColor;

void main()
{
	gl_Position = modelViewProjectionMatrix * vec4( position, 1 );
	vertexColor = color;
}
