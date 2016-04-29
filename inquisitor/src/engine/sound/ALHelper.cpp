#include "ALHelper.hpp"

namespace ALHelper
{
	std::string GetOpenALErrorString( const ALenum error )
	{
		switch( error )
		{
			case AL_NO_ERROR:
				return( "AL_NO_ERROR" );

			case AL_INVALID_NAME:
				return( "AL_INVALID_NAME" );

			case AL_INVALID_ENUM:
				return( "AL_INVALID_ENUM" );

			case AL_INVALID_VALUE:
				return( "AL_INVALID_VALUE" );

			case AL_INVALID_OPERATION:
				return( "AL_INVALID_OPERATION" );

			case AL_OUT_OF_MEMORY:
				return( "AL_OUT_OF_MEMORY" );

			default:
				return( "UNKNOWN ERROR" );
		}
	}
}
