in vec3 Normal;
in vec3 Position;

uniform samplerCube skyBoxTexture;

out vec4 color;

void main()
{
    const vec3 I = normalize( Position - Camera.position );
    const vec3 R = reflect( I, normalize( Normal ) );

    color = texture( skyBoxTexture, R );
}
