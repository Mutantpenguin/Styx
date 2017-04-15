uniform sampler2D fgTexture;

in vec2 UVfg;

out vec4 color;

void main()
{
	color = texture2D( fgTexture, UVfg );
}
