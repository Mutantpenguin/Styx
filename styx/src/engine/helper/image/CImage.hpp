#ifndef CIMAGE_HPP
#define CIMAGE_HPP

#include <memory>
#include <vector>
#include <string>

#include "src/engine/helper/CSize.hpp"

class CImage final
{
public:
	using PixelBuffer = std::vector< std::uint8_t >;

public:
	CImage( const CSize &size, const CSize &originalSize, bool alpha, std::uint8_t bpp, std::uint32_t pitch, std::unique_ptr< PixelBuffer > imageData );

	const CSize &Size( void ) const;

	const CSize &OriginalSize( void ) const;

	bool HasAlpha( void ) const;

	std::uint8_t BPP( void ) const;

	std::uint32_t Pitch( void ) const;

	const std::uint8_t *RawPixelData( void ) const;

private:
	const CSize			m_size;
	const CSize			m_originalSize;
	const bool			m_alpha;
	const std::uint8_t	m_bpp;
	const std::uint32_t	m_pitch;

	const std::unique_ptr< PixelBuffer > m_imageData;
};

#endif // CIMAGE_HPP
