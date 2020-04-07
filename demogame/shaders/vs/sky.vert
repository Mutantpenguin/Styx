out vec3 TexCoords;

void main()
{
    gl_Position = ( View.projectionMatrix * mat4( mat3( View.viewMatrix ) ) * vec4( position, 1.0 ) ).xyww;
    TexCoords = position;
}
