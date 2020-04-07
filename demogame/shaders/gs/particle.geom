layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in vec3 Normal[];

out vec2 UV;
flat out int textureIndexOffset;

uniform float scale;

void main()
{
    vec4 P = gl_in[ 0 ].gl_Position;

	float halfSize = 0.5 * scale;

	// a: left-bottom 
	vec2 va = P.xy + vec2( -halfSize, -halfSize );
	gl_Position = View.projectionMatrix * vec4( va, P.zw );
	UV = vec2( 0.0, 0.0 );
	textureIndexOffset = int( Normal[ 0 ].x );
	EmitVertex();  

	// b: left-top
	vec2 vb = P.xy + vec2( -halfSize, halfSize );
	gl_Position = View.projectionMatrix * vec4( vb, P.zw );
	UV = vec2( 0.0, 1.0 );
	textureIndexOffset = int( Normal[ 0 ].x );
	EmitVertex();  

	// d: right-bottom
	vec2 vd = P.xy + vec2( halfSize, -halfSize );
	gl_Position = View.projectionMatrix * vec4( vd, P.zw );
	UV = vec2( 1.0, 0.0 );
	textureIndexOffset = int( Normal[ 0 ].x );
	EmitVertex();  

	// c: right-top
	vec2 vc = P.xy + vec2( halfSize, halfSize );
	gl_Position = View.projectionMatrix * vec4( vc, P.zw );
	UV = vec2( 1.0, 1.0 );
	textureIndexOffset = int( Normal[ 0 ].x );
	EmitVertex();  
	
    EndPrimitive();
}