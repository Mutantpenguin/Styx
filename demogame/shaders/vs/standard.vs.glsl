layout( location = 0 ) in vec3 vertex;
layout( location = 1 ) in vec3 normal;
layout( location = 2 ) in vec2 texcoord;

layout( location = 0 ) uniform mat4 modelViewProjectionMatrix;
layout( location = 1 ) uniform mat3 textureMatrix;

out vec2 UV;

void main()
{
	gl_Position = modelViewProjectionMatrix * vec4( vertex, 1 );

	UV = ( textureMatrix * vec3( texcoord, 1 ) ).st;
}
