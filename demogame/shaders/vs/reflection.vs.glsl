out vec3 Normal;
out vec3 Position;

void main()
{
    gl_Position = modelViewProjectionMatrix * vec4( vertex, 1.0f );
    Normal = mat3( transpose( inverse( modelMatrix ) ) ) * normal;
    Position = vec3( modelMatrix * vec4( vertex, 1.0f ) );
}
