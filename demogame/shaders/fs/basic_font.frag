uniform sampler2D fontTexture;

in vec2 UV;

out vec4 color;

void main()
{
	vec4 c = texture( fontTexture, UV );
	
	color = vec4( c.r, c.r, c.r, c.r );
}
