#include "CImage.hpp"

#include <cassert>

CImage::CImage( const CSize &size, const CSize &originalSize, bool alpha, unsigned char bpp, unsigned int pitch, std::unique_ptr< PixelBuffer > imageData ) :
	m_size( size ),
	m_originalSize( originalSize ),
	m_alpha( alpha ),
	m_bpp( bpp ),
	m_pitch( pitch ),
	m_imageData( std::move( imageData ) )
{
	assert( m_imageData );
}

const CSize &CImage::Size( void ) const
{
	return( m_size );
}

const CSize &CImage::OriginalSize( void ) const
{
	return( m_originalSize );
}

bool CImage::HasAlpha( void ) const
{
	return( m_alpha );
}

unsigned char CImage::BPP( void ) const
{
	return( m_bpp );
}

unsigned int CImage::Pitch( void ) const
{
	return( m_pitch );
}

const unsigned char *CImage::RawPixelData( void ) const
{
	return( m_imageData->data() );
}
