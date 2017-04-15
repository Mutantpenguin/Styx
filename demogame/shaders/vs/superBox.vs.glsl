uniform float bgRadsPerSecond;
uniform float fgRadsPerSecond;

uniform vec2 bgScale;

out vec3 Normal;
out vec3 Position;

out vec2 UVbg;
out vec2 UVfg;

void main()
{
	gl_Position = modelViewProjectionMatrix * vec4( vertex, 1 );

	const vec2 translation = vec2( 0.5f, 0.5f );

	const float bgAngle = Timer.time * bgRadsPerSecond / 1000;
	const float fgAngle = Timer.time * fgRadsPerSecond / 1000;

	const float bgAngleCos = cos( bgAngle );
	const float bgAngleSin = sin( bgAngle );

	const float fgAngleCos = cos( fgAngle );
	const float fgAngleSin = sin( fgAngle );

	const mat2 bgScaleMat = mat2(	1.0f / bgScale.s,	0.0f,
									0.0f,				1.0f / bgScale.t );

	UVbg = ( ( mat2( bgAngleCos, bgAngleSin, -bgAngleSin, bgAngleCos  ) * ( texcoord - translation ) ) * bgScaleMat ) + translation;

	UVfg = ( mat2( fgAngleCos, fgAngleSin, -fgAngleSin, fgAngleCos  ) * ( texcoord - translation ) ) + translation;

	Normal = mat3( transpose( inverse( modelMatrix ) ) ) * normal;
    Position = vec3( modelMatrix * vec4( vertex, 1.0f ) );
}
