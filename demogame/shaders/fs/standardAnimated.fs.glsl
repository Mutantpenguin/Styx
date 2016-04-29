[uniformBlockTimer]

uniform sampler2DArray diffuseTexture;

in vec2 UV;

out vec4 color;

void main()
{
	int layerCount = textureSize( diffuseTexture, 0 ).z;

	color = texture( diffuseTexture, vec3( UV.x, UV.y, int( timer.time / 100.0 ) % layerCount ) ).rgba;
}
