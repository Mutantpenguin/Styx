#include "CCubemapData.hpp"

#include "../../logger/CLogger.hpp"

bool CCubemapData::AddFace( const unsigned char faceNum, const std::shared_ptr< const CImage > &image )
{
	if( faceNum >= countCubemapFaces )
	{
		LOG( logWARNING ) << "face '" << faceNum << "' is not a valid cubemap face";
		return( false );
	}

	if( faceNum > 0 )
	{
		if( !m_faces[ faceNum - 1 ] )
		{
			LOG( logWARNING ) << "cannot add face '" << faceNum << "' to cubemap when face '" << faceNum - 1 << "' is not already added";
			return( false );
		}
	}

	if( m_faces[ faceNum ] )
	{
		LOG( logWARNING ) << "cubemap face '" << faceNum << "' already exists";
		return( false );
	}

	// check newly added faces against the first image if already existant
	const std::shared_ptr< const CImage > &firstImage = m_faces[ 0 ];
	if( firstImage )
	{
		if( firstImage->Size() != image->Size() )
		{
			LOG( logWARNING ) << "different faces in cubemaps must have the same size";
			return( false );
		}
		else if( firstImage->BPP() != image->BPP() )
		{
			LOG( logWARNING ) << "different faces in cubemaps must have the same bpp";
			return( false );
		}
		else if( firstImage->HasAlpha() != image->HasAlpha() )
		{
			LOG( logWARNING ) << "different faces in cubemaps must have the same alpha";
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
