uniform sampler2D skullTexture;
uniform sampler2D waitTexture;

in vec2 UVskull;
in vec2 UVwait;

out vec4 color;

void main()
{
	const vec4 skull = texture2D( skullTexture, UVskull );
    const vec4 wait = texture2D( waitTexture, UVwait );

	color = mix( skull, wait, wait.a );
}
