uniform sampler2D diffuseTexture;

in vec2 UV;

out vec4 color;

void main()
{
	const float strength = 0.02;

	const vec2 freq = vec2( 6.0, 7.0 );

	const vec2 uv = UV + cos( Timer.time / 1000.0 * freq + UV * 10.0 ) * strength;

	color = texture2D( diffuseTexture, uv );
}
