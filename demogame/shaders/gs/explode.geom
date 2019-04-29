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
   return( normalize( cross( a, b ) ) );
}

vec3 explode( vec3 normal )
{
    float magnitude = 4.0;
    vec3 direction = normal * ( ( sin( Timer.time / 300.0 ) + 1.0 ) / 2.0 ) * magnitude; 
    return( direction );
}

void main()
{
	vec4 faceNormalExploded = vec4( explode( GetNormal() ), 0.0 );

    gl_Position = modelViewProjectionMatrix * ( gl_in[ 0 ].gl_Position - faceNormalExploded );
    UV = gs_in[ 0 ].UV;
    EmitVertex();
    
	gl_Position = modelViewProjectionMatrix * ( gl_in[ 1 ].gl_Position - faceNormalExploded );
    UV = gs_in[ 1 ].UV;
    EmitVertex();
    
	gl_Position = modelViewProjectionMatrix * ( gl_in[ 2 ].gl_Position - faceNormalExploded );
    UV = gs_in[ 2 ].UV;
    EmitVertex();
	
    EndPrimitive();
}