uniform sampler2D bgTexture;
uniform sampler2D fgTexture;
uniform samplerCube skyBoxTexture;

in vec3 Normal;
in vec3 Position;

in vec2 UVbg;
in vec2 UVfg;

out vec4 color;

void main()
{
	const vec4 bg = texture2D( bgTexture, UVbg );
    const vec4 fg = texture2D( fgTexture, UVfg );

	const vec3 I = normalize( Position - Camera.position );
    const vec3 R = reflect( I, normalize( Normal ) );

    const vec4 sky = texture( skyBoxTexture, R );

	const vec4 temp = mix( bg, sky, 0.25 );

	color = mix( temp, fg, fg.a );
}
