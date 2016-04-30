uniform sampler2D diffuseTexture;

layout( location = 4 ) uniform vec4 mainColor;

out vec4 color;

void main()
{
	color = mainColor;
}
