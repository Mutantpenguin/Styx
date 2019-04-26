uniform float bgRadsPerSecond;

uniform vec2 bgScale;

out vec2 UV;

void main()
{
	const vec2 translation = vec2( -0.5f, 0.5f );

	const mat2 bgScaleMat = mat2(	1.0f / bgScale.s,	0.0f,
									0.0f,				1.0f / bgScale.t );

	const float bgAngle = Timer.time * bgRadsPerSecond / 1000;

	const float bgAngleCos = cos( bgAngle );
	const float bgAngleSin = sin( bgAngle );

	UV = ( ( mat2( bgAngleCos, bgAngleSin, -bgAngleSin, bgAngleCos  ) * ( uv0 - translation ) ) * bgScaleMat ) + translation;

	gl_Position = modelViewProjectionMatrix * vec4( position, 1 );
}
