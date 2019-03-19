layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

out vec2 UV;

uniform float scale;

void main()
{
    vec4 P = gl_in[ 0 ].gl_Position;

	float halfSize = 0.5 * scale;

	// a: left-bottom 
	vec2 va = P.xy + vec2( -halfSize, -halfSize );
	gl_Position = Camera.projectionMatrix * vec4( va, P.zw );
	UV = vec2( 0.0, 0.0 );
	EmitVertex();  

	// b: left-top
	vec2 vb = P.xy + vec2( -halfSize, halfSize );
	gl_Position = Camera.projectionMatrix * vec4( vb, P.zw );
	UV = vec2( 0.0, 1.0 );
	EmitVertex();  

	// d: right-bottom
	vec2 vd = P.xy + vec2( halfSize, -halfSize );
	gl_Position = Camera.projectionMatrix * vec4( vd, P.zw );
	UV = vec2( 1.0, 0.0 );
	EmitVertex();  

	// c: right-top
	vec2 vc = P.xy + vec2( halfSize, halfSize );
	gl_Position = Camera.projectionMatrix * vec4( vc, P.zw );
	UV = vec2( 1.0, 1.0 );
	EmitVertex();  
	
    EndPrimitive();
}