out vec3 Normal;

void main()
{
	gl_Position = modelViewMatrix * vec4( position, 1 );
	Normal = normal;
}
