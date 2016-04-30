[uniformBlockTimer]

uniform sampler2DArray diffuseTexture;

uniform uint animDelay;

in vec2 UV;

out vec4 color;

void main()
{
	int layerCount = textureSize( diffuseTexture, 0 ).z;

	color = texture( diffuseTexture, vec3( UV.x, UV.y, int( timer.time / animDelay ) % layerCount ) ).rgba;
}
