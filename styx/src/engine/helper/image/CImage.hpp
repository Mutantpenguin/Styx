#pragma once

#include <memory>
#include <vector>
#include <string>

#include "src/engine/helper/Types.hpp"

#include "src/engine/helper/CSize.hpp"

class CImage final
{
public:
	using PixelBuffer = std::vector< u8 >;

public:
	CImage( const CSize &size, const CSize &originalSize, bool alpha, u8 bpp, u32 pitch, std::unique_ptr< PixelBuffer > imageData );

	const CSize &Size() const;

	const CSize &OriginalSize() const;

	bool HasAlpha() const;

	u8 BPP() const;

	u32 Pitch() const;

	const u8 *RawPixelData() const;

private:
	const CSize	m_size;
	const CSize	m_originalSize;
	const bool	m_alpha;
	const u8	m_bpp;
	const u32	m_pitch;

	const std::unique_ptr< PixelBuffer > m_imageData;
};
