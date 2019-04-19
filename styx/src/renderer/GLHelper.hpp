#pragma once

#include <glm/glm.hpp>

#include "src/renderer/GL.h"

#include "src/helper/image/CImage.hpp"

#include "src/core/StyxException.hpp"

namespace GLHelper
{
	bool DstBlendFuncFromString( const std::string &string, GLenum &dstblend );
	bool SrcBlendFuncFromString( const std::string &string, GLenum &srcblend );

	bool FaceModeFromString( const std::string &string, GLenum &facemode );
	bool PolygonModeFromString( const std::string &string, GLenum &polygonmode );

	GLenum GLFormatFromImage( const std::shared_ptr< const CImage > &image );

	std::string GLSLTypeToString( const GLenum type );

	template<typename T>
	GLenum glmTypeToGLSLType()
	{
		const std::type_info &type = typeid( T );

		if( type == typeid( glm::vec4 ) )
		{
			return( GL_FLOAT_VEC4 );
		}
		else if( type == typeid( glm::vec3 ) )
		{
			return( GL_FLOAT_VEC3 );
		}
		else if( type == typeid( glm::vec2 ) )
		{
			return( GL_FLOAT_VEC2 );
		}
		else if( type == typeid( glm::mat4 ) )
		{
			return( GL_FLOAT_MAT4 );
		}
		else if( type == typeid( glm::mat3 ) )
		{
			return( GL_FLOAT_MAT3 );
		}
		else if( type == typeid( glm::uint ) )
		{
			return( GL_UNSIGNED_INT );
		}
		else
		{
			THROW_STYX_EXCEPTION( "unhandled type: {0}", type.name() )
		}
	}
}
