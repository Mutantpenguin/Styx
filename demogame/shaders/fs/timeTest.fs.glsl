[uniformBlockTimer]

uniform sampler2D diffuseTexture;

in vec2 UV;

out vec4 color;

void main()
{
	color = texture( diffuseTexture, UV * sin( timer.time / 1000.0 ) ).rgba;
}
