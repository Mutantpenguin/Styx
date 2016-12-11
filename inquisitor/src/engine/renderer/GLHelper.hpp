#ifndef GLHELP_HPP
#define GLHELP_HPP

#include <glm/glm.hpp>

#include "GL.h"

#include "../helper/image/CImage.hpp"

namespace GLHelper
{
	bool DstBlendFuncFromString( const std::string &string, GLenum &dstblend );
	bool SrcBlendFuncFromString( const std::string &string, GLenum &srcblend );

	bool FaceModeFromString( const std::string &string, GLenum &facemode );
	bool PolygonModeFromString( const std::string &string, GLenum &polygonmode );

	bool isFramebufferComplete( void );

	GLenum GLFormatFromImage( const std::shared_ptr< const CImage > &image );

	std::string GLSLTypeToString( GLenum type );

	template<typename T>
	GLenum glmTypeToGLSLType( void )
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
			throw std::exception();
		}
	}
}

#endif // GLHELP_HPP
