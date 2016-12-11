#ifndef CIMAGE_HPP
#define CIMAGE_HPP

#include <memory>
#include <vector>
#include <string>

#include "src/engine/helper/CSize.hpp"

class CImage final
{
public:
	typedef std::vector< unsigned char > PixelBuffer;

public:
	CImage( const CSize &size, const CSize &originalSize, bool alpha, unsigned char bpp, unsigned int pitch, std::unique_ptr< PixelBuffer > imageData );

	const CSize &Size( void ) const;

	const CSize &OriginalSize( void ) const;

	bool HasAlpha( void ) const;

	unsigned char BPP( void ) const;

	unsigned int Pitch( void ) const;

	const unsigned char *RawPixelData( void ) const;

private:
	CSize			m_size;
	CSize			m_originalSize;
	bool			m_alpha;
	unsigned char	m_bpp;
	unsigned int	m_pitch;

	std::unique_ptr< PixelBuffer > m_imageData;
};

#endif // CIMAGE_HPP
