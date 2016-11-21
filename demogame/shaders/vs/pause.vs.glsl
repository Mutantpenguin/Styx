layout( location = 0 ) in vec3 vertex;
layout( location = 2 ) in vec2 texcoord;

layout( location = 1 ) uniform mat3 textureMatrix;

out vec2 UV;

void main()
{
	gl_Position = vec4( vertex.xy, 0.0, 1.0 );

	UV = ( textureMatrix * vec3( texcoord, 1 ) ).st;
}
