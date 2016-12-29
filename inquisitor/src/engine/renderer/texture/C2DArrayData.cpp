#include "C2DArrayData.hpp"

#include "src/engine/logger/CLogger.hpp"

bool C2DArrayData::AddLayer( const std::shared_ptr< const CImage > &image )
{
	// check newly added layer against the first image if already existant
	if( !m_layers.empty() )
	{
		const std::shared_ptr< const CImage > &firstImage = m_layers.front();

		if( firstImage->Size() != image->Size() )
		{
			logWARNING( "different layers in array textures must have the same size" );
			return( false );
		}
		else if( firstImage->BPP() != image->BPP() )
		{
			logWARNING( "different layers in array textures must have the same bpp" );
			return( false );
		}
		else if( firstImage->HasAlpha() != image->HasAlpha() )
		{
			logWARNING( "different layers in array textures must have the same alpha" );
			return( false );
		};
	}

	m_layers.push_back( image );

	return( true );
}

const std::vector< std::shared_ptr< const CImage > > &C2DArrayData::getLayers( void ) const
{
	return( m_layers );
}
