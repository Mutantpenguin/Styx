#include "CCubemapData.hpp"

#include "src/engine/logger/CLogger.hpp"

bool CCubemapData::AddFace( const unsigned char faceNum, const std::shared_ptr< const CImage > &image )
{
	if( faceNum >= countCubemapFaces )
	{
		logWARNING( "face '{0}' is not a valid cubemap face", faceNum );
		return( false );
	}

	if( faceNum > 0 )
	{
		if( !m_faces[ faceNum - 1 ] )
		{
			logWARNING( "cannot add face '{0}' to cubemap when face '{1}' is not already added", faceNum, faceNum - 1 );
			return( false );
		}
	}

	if( m_faces[ faceNum ] )
	{
		logWARNING( "cubemap face '{0}' already exists", faceNum );
		return( false );
	}

	// check newly added faces against the first image if already existant
	const std::shared_ptr< const CImage > &firstImage = m_faces[ 0 ];
	if( firstImage )
	{
		if( firstImage->Size() != image->Size() )
		{
			logWARNING( "different faces in cubemaps must have the same size" );
			return( false );
		}
		else if( firstImage->BPP() != image->BPP() )
		{
			logWARNING( "different faces in cubemaps must have the same bpp" );
			return( false );
		}
		else if( firstImage->HasAlpha() != image->HasAlpha() )
		{
			logWARNING( "different faces in cubemaps must have the same alpha" );
			return( false );
		};
	}

	m_faces[ faceNum ] = image;

	return( true );
}

const std::array< std::shared_ptr< const CImage >, 6 > &CCubemapData::getFaces( void ) const
{
	return( m_faces );
}

bool CCubemapData::isComplete( void ) const
{
	for( const std::shared_ptr< const CImage > &i : m_faces )
	{
		if( !i )
		{
			return( false );
		}
	}

	return( true );
}
