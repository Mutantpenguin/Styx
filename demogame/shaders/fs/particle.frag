
uniform sampler2DArray diffuseTexture;

uniform uint animDelay;

in vec2 UV;
flat in int textureIndexOffset;

out vec4 color;

void main()
{
	int layerCount = textureSize( diffuseTexture, 0 ).z;

	color = texture( diffuseTexture, vec3( UV.x, UV.y, ( int( Timer.time / animDelay ) + textureIndexOffset ) % layerCount ) ).rgba;
}
