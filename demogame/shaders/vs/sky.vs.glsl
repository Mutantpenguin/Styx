layout( location = 0 ) in vec3 vertex;

[uniformBlockCamera]

out vec3 TexCoords;

void main()
{
    gl_Position = ( cam.projectionMatrix * mat4( mat3( cam.viewMatrix ) ) * vec4( vertex, 1.0 ) ).xyww;
    TexCoords = vertex;
}
