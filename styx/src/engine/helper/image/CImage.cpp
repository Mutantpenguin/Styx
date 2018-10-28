#include "CImage.hpp"

#include <cassert>

CImage::CImage( const CSize &size, const CSize &originalSize, bool alpha, u8 bpp, u32 pitch, std::unique_ptr< PixelBuffer > imageData ) :
	m_size { size },
	m_originalSize { originalSize },
	m_alpha { alpha },
	m_bpp { bpp },
	m_pitch { pitch },
	m_imageData { std::move( imageData ) }
{
	assert( m_imageData );
}

const CSize &CImage::Size() const
{
	return( m_size );
}

const CSize &CImage::OriginalSize() const
{
	return( m_originalSize );
}

bool CImage::HasAlpha() const
{
	return( m_alpha );
}

u8 CImage::BPP() const
{
	return( m_bpp );
}

u32 CImage::Pitch() const
{
	return( m_pitch );
}

const u8 *CImage::RawPixelData() const
{
	return( m_imageData->data() );
}
