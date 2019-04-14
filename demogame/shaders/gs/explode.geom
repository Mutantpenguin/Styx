layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT
{
	vec2 UV;
} gs_in [];

out vec2 UV;

vec3 GetNormal()
{
   vec3 a = vec3( gl_in[ 0 ].gl_Position ) - vec3( gl_in[ 1 ].gl_Position );
   vec3 b = vec3( gl_in[ 2 ].gl_Position ) - vec3( gl_in[ 1 ].gl_Position );
   return normalize( cross( a, b ) );
}

vec4 explode( vec4 position, vec3 normal )
{
    float magnitude = 4.0;
    vec3 direction = normal * ( ( sin( Timer.time / 1000.0 ) + 1.0 ) / 2.0 ) * magnitude; 
    return position + vec4( direction, 0.0 );
}

void main()
{
    vec3 normal = GetNormal();

    gl_Position = explode( gl_in[ 0 ].gl_Position, normal );
    UV = gs_in[ 0 ].UV;
    EmitVertex();
    
	gl_Position = explode( gl_in[ 1 ].gl_Position, normal );
    UV = gs_in[ 1 ].UV;
    EmitVertex();
    
	gl_Position = explode( gl_in[ 2 ].gl_Position, normal );
    UV = gs_in[ 2 ].UV;
    EmitVertex();
	
    EndPrimitive();
}