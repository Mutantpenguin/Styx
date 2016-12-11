out vec3 TexCoords;

void main()
{
    gl_Position = ( Camera.projectionMatrix * mat4( mat3( Camera.viewMatrix ) ) * vec4( vertex, 1.0 ) ).xyww;
    TexCoords = vertex;
}
