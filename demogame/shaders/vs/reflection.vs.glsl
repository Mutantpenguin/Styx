layout( location = 0 ) in vec3 vertex;
layout( location = 1 ) in vec3 normal;

layout( location = 0 ) uniform mat4 modelViewProjectionMatrix;
layout( location = 2 ) uniform mat4 modelMatrix;

out vec3 Normal;
out vec3 Position;

[uniformBlockCamera]

out vec3 TexCoords;

void main()
{
    gl_Position = modelViewProjectionMatrix * vec4( vertex, 1.0f );
    Normal = mat3( transpose( inverse( modelMatrix ) ) ) * normal;
    Position = vec3( modelMatrix * vec4( vertex, 1.0f ) );
}
