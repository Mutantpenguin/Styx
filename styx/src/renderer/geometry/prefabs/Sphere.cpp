#include "Sphere.hpp"

#include <glm/gtc/constants.hpp>

namespace GeometryPrefabs
{
	const u16 MinSectorCount = 3;
	const u16 MinStackCount = 2;
	
	// TODO tidy up, rework comments
	
	Geometry<VertexP> SphereP( u16 sectorCount, u16 stackCount, const f16 radius )
	{
		sectorCount = std::max( sectorCount, MinSectorCount );
		stackCount = std::max( stackCount, MinStackCount );
		
		Geometry<VertexP> geometry;
		
		geometry.Mode = GL_TRIANGLES;

		const f16 sectorStep = glm::two_pi<f16>() / sectorCount;
		const f16 stackStep = glm::pi<f16>() / stackCount;

		for( u16 i = 0; i <= stackCount; ++i )
		{
			const f16 stackAngle = glm::half_pi<f16>() - i * stackStep;        // starting from pi/2 to -pi/2
			const f16 xz = radius * cosf( stackAngle );             // r * cos(u)
			const f16 y = radius * sinf( stackAngle );              // r * sin(u)

			// add (sectorCount+1) vertices per stack
			// the first and last vertices have same position and normal, but different tex coords
			for( u16 j = 0; j <= sectorCount; ++j )
			{
				const f16 sectorAngle = j * sectorStep;           // starting from 0 to 2pi

				// vertex position
				const f16 x = xz * cosf( sectorAngle );             // r * cos(u) * cos(v)
				const f16 z = xz * sinf( sectorAngle );             // r * cos(u) * sin(v)
				
				VertexP vertex;
				// position
				vertex.Position.x = x;
				vertex.Position.y = y;
				vertex.Position.z = z;
				
				geometry.Vertices.push_back( vertex );
			}
		}

		// indices
		//  k1--k1+1
		//  |  / |
		//  | /  |
		//  k2--k2+1

		for( u16 i = 0; i < stackCount; ++i )
		{
			u16 k1 = i * ( sectorCount + 1 );     // beginning of current stack
			u16 k2 = k1 + sectorCount + 1;      // beginning of next stack

			for( u16 j = 0; j < sectorCount; ++j, ++k1, ++k2 )
			{
				// 2 triangles per sector excluding 1st and last stacks
				if( i != 0 )
				{
					// k1---k2---k1+1
					geometry.Indices.push_back( k1 );
					geometry.Indices.push_back( k1+1 );
					geometry.Indices.push_back( k2 );
				}

				if( i != ( stackCount - 1 ) )
				{
					// k1+1---k2---k2+1
					geometry.Indices.push_back( k1+1 );
					geometry.Indices.push_back( k2+1 );
					geometry.Indices.push_back( k2 );
				}
			}
		}
		
		return( geometry );
	}

	Geometry<VertexPU0> SpherePU0( u16 sectorCount, u16 stackCount, const f16 radius )
	{
		sectorCount = std::max( sectorCount, MinSectorCount );
		stackCount = std::max( stackCount, MinStackCount );
		
		Geometry<VertexPU0> geometry;
		
		geometry.Mode = GL_TRIANGLES;

		const f16 sectorStep = glm::two_pi<f16>() / sectorCount;
		const f16 stackStep = glm::pi<f16>() / stackCount;

		for( u16 i = 0; i <= stackCount; ++i )
		{
			const f16 stackAngle = glm::half_pi<f16>() - i * stackStep;        // starting from pi/2 to -pi/2
			const f16 xz = radius * cosf( stackAngle );             // r * cos(u)
			const f16 y = radius * sinf( stackAngle );              // r * sin(u)

			// add (sectorCount+1) vertices per stack
			// the first and last vertices have same position and normal, but different tex coords
			for( u16 j = 0; j <= sectorCount; ++j )
			{
				const f16 sectorAngle = j * sectorStep;           // starting from 0 to 2pi

				// vertex position
				const f16 x = xz * cosf( sectorAngle );             // r * cos(u) * cos(v)
				const f16 z = xz * sinf( sectorAngle );             // r * cos(u) * sin(v)
				
				VertexPU0 vertex;
				// position
				vertex.Position.x = x;
				vertex.Position.y = y;
				vertex.Position.z = z;
				// vertex tex coord between [0, 1]
				vertex.UV0.s = (f16)j / sectorCount;
				vertex.UV0.t = (f16)i / stackCount;
				
				geometry.Vertices.push_back( vertex );
			}
		}

		// indices
		//  k1--k1+1
		//  |  / |
		//  | /  |
		//  k2--k2+1

		for( u16 i = 0; i < stackCount; ++i )
		{
			u16 k1 = i * ( sectorCount + 1 );     // beginning of current stack
			u16 k2 = k1 + sectorCount + 1;      // beginning of next stack

			for( u16 j = 0; j < sectorCount; ++j, ++k1, ++k2 )
			{
				// 2 triangles per sector excluding 1st and last stacks
				if( i != 0 )
				{
					// k1---k2---k1+1
					geometry.Indices.push_back( k1 );
					geometry.Indices.push_back( k1+1 );
					geometry.Indices.push_back( k2 );
				}

				if( i != ( stackCount - 1 ) )
				{
					// k1+1---k2---k2+1
					geometry.Indices.push_back( k1+1 );
					geometry.Indices.push_back( k2+1 );
					geometry.Indices.push_back( k2 );
				}
			}
		}
		
		return( geometry );
	}

	Geometry<VertexPNU0> SpherePNU0( u16 sectorCount, u16 stackCount, const f16 radius )
	{
		sectorCount = std::max( sectorCount, MinSectorCount );
		stackCount = std::max( stackCount, MinStackCount );
		
		Geometry<VertexPNU0> geometry;

		geometry.Mode = GL_TRIANGLES;

		const f16 sectorStep = glm::two_pi<f16>() / sectorCount;
		const f16 stackStep = glm::pi<f16>() / stackCount;

		const f16 lengthInv = 1.0f / radius;

		for( u16 i = 0; i <= stackCount; ++i )
		{
			const f16 stackAngle = glm::half_pi<f16>() - i * stackStep;        // starting from pi/2 to -pi/2
			const f16 xz = radius * cosf( stackAngle );             // r * cos(u)
			const f16 y = radius * sinf( stackAngle );              // r * sin(u)

			// add (sectorCount+1) vertices per stack
			// the first and last vertices have same position and normal, but different tex coords
			for( u16 j = 0; j <= sectorCount; ++j )
			{
				const f16 sectorAngle = j * sectorStep;           // starting from 0 to 2pi

				// vertex position
				const f16 x = xz * cosf( sectorAngle );             // r * cos(u) * cos(v)
				const f16 z = xz * sinf( sectorAngle );             // r * cos(u) * sin(v)

				VertexPNU0 vertex;
				// position
				vertex.Position.x = x;
				vertex.Position.y = y;
				vertex.Position.z = z;
				// normal
				vertex.Normal.x = x * lengthInv;
				vertex.Normal.y = y * lengthInv;
				vertex.Normal.z = z * lengthInv;
				// vertex tex coord between [0, 1]
				vertex.UV0.s = (f16)j / sectorCount;
				vertex.UV0.t = (f16)i / stackCount;

				geometry.Vertices.push_back( vertex );
			}
		}

		// indices
		//  k1--k1+1
		//  |  / |
		//  | /  |
		//  k2--k2+1

		for( u16 i = 0; i < stackCount; ++i )
		{
			u16 k1 = i * ( sectorCount + 1 );     // beginning of current stack
			u16 k2 = k1 + sectorCount + 1;      // beginning of next stack

			for( u16 j = 0; j < sectorCount; ++j, ++k1, ++k2 )
			{
				// 2 triangles per sector excluding 1st and last stacks
				if( i != 0 )
				{
					// k1---k2---k1+1
					geometry.Indices.push_back( k1 );
					geometry.Indices.push_back( k1 + 1 );
					geometry.Indices.push_back( k2 );
				}

				if( i != ( stackCount - 1 ) )
				{
					// k1+1---k2---k2+1
					geometry.Indices.push_back( k1 + 1 );
					geometry.Indices.push_back( k2 + 1 );
					geometry.Indices.push_back( k2 );
				}
			}
		}

		return( geometry );
	}
}