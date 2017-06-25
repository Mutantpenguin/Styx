out vec3 Normal;
out vec3 Position;

void main()
{
    gl_Position = modelViewProjectionMatrix * vec4( position, 1.0f );
    Normal = mat3( transpose( inverse( modelMatrix ) ) ) * normal;
    Position = vec3( modelMatrix * vec4( position, 1.0f ) );
}
