uniform float bgRadsPerSecond;

uniform vec2 bgScale;

out vec2 UVbg;

void main()
{
	const vec2 translation = vec2( 0.25f, 0.25f );

	const mat2 bgScaleMat = mat2(	1.0f / bgScale.s,	0.0f,
									0.0f,				1.0f / bgScale.t );

	const float bgAngle = Timer.time * bgRadsPerSecond / 1000;

	const float bgAngleCos = cos( bgAngle );
	const float bgAngleSin = sin( bgAngle );

	UVbg = ( ( mat2( bgAngleCos, bgAngleSin, -bgAngleSin, bgAngleCos  ) * ( texcoord - translation ) ) * bgScaleMat ) + translation;

	gl_Position = vec4( vertex.xy, 0.0, 1.0 );
}
