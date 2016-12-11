out vec4 color;

const vec4 green = { 0.0, 1.0, 0.0, 1.0 };
const vec4 red = { 1.0, 0.0, 0.0, 1.0 };

void main()
{
	// limit weight between 0 and 1
	float weight = ( sin( Timer.time / 2000.0 ) + 1 ) / 2;

	color = ( weight * red ) + ( ( 1 - weight ) * green );
}
