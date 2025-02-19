#include "CImage.hpp"

#include <cassert>

CImage::CImage( const CSize &size, u8 bpp, u32 pitch, std::unique_ptr<PixelBuffer> imageData ) :
	m_size { size },
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

u8 CImage::BPP() const
{
	return( m_bpp );
}

u32 CImage::Pitch() const
{
	return( m_pitch );
}

const std::byte *CImage::RawPixelData() const
{
	return( m_imageData->data() );
}
