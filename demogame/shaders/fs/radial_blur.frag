uniform sampler2D diffuseTexture;

uniform vec2 radialSize;    // texel size

uniform float radialBlur;   // blur factor
uniform float radialBright; // bright factor

uniform vec2 radialOrigin;  // blur origin

in vec2 UV;

out vec4 color;

void main(void)
{
	vec2 TexCoord = UV;

	vec4 SumColor = vec4( 0.0, 0.0, 0.0, 0.0 );
	TexCoord += radialSize * 0.5 - radialOrigin;

	for( int i = 0; i < 12; i++ )
	{
		float scale = 1.0 - radialBlur * ( float( i ) / 11.0 );
		SumColor += texture2D( diffuseTexture, TexCoord * scale + radialOrigin );
	}

	color = SumColor / 12.0 * radialBright;
}
