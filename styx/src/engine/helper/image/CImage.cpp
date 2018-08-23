#include "CImage.hpp"

#include <cassert>

CImage::CImage( const CSize &size, const CSize &originalSize, bool alpha, std::uint8_t bpp, std::uint32_t pitch, std::unique_ptr< PixelBuffer > imageData ) :
	m_size { size },
	m_originalSize { originalSize },
	m_alpha { alpha },
	m_bpp { bpp },
	m_pitch { pitch },
	m_imageData { std::move( imageData ) }
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

std::uint8_t CImage::BPP( void ) const
{
	return( m_bpp );
}

std::uint32_t CImage::Pitch( void ) const
{
	return( m_pitch );
}

const std::uint8_t *CImage::RawPixelData( void ) const
{
	return( m_imageData->data() );
}
