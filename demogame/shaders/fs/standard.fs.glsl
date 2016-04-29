uniform sampler2D diffuseTexture;

in vec2 UV;

out vec4 color;

void main()
{
	color = texture( diffuseTexture, UV ).rgba;
}
