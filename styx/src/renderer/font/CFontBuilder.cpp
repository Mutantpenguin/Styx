#include "CFontBuilder.hpp"

#include <array>

#include "external/stb/stb_truetype.h"

#include "src/core/StyxException.hpp"

#include "src/logger/CLogger.hpp"

#include "src/helper/image/CImage.hpp"

#include "src/core/FileExtension.hpp"

#include "src/renderer/texture/CTextureLoader.hpp"


const std::shared_ptr<CFont> CFontBuilder::FromFile( const fs::path &path, const u16 size, const CGlyphRange &glyphRange ) const
{
	if( !path.has_filename() )
	{
		logWARNING( "path '{0}' does not containt a filename", path.generic_string() );
		return( FromDummy() );
	}

	const std::string fileExtensionString = path.extension().generic_string();

	if( fileExtensionString != FileExtension::Font::ttf )
	{
		logWARNING( "file type '{0}' of font file '{1}' is not supported", fileExtensionString, path.generic_string() );
		return( FromDummy() );
	}
	else if( !m_filesystem.Exists( path ) )
	{
		logWARNING( "font file '{0}' does not exist", path.generic_string() );
		return( FromDummy() );
	}
	else
	{
		auto font = FromTtfFile( path, size, glyphRange );
		
		if( nullptr == font )
		{
			return( FromDummy() );
		}
		else
		{
			return( font );
		}
	}
	
}

const std::shared_ptr<CFont> CFontBuilder::FromTtfFile( const fs::path &path, const u16 size, const CGlyphRange &glyphRange ) const
{
	auto font = std::make_shared<CFont>();
	
	font->Size = size;
	
	font->AtlasSize = { 4096, 4096 };
	// TODO font->AtlasSize = { 512, 512 };
	
	auto fontImageData = std::make_unique<CImage::PixelBuffer>( font->AtlasSize.width * font->AtlasSize.height );
	
	stbtt_pack_context context;
	if( !stbtt_PackBegin( &context, reinterpret_cast<unsigned char*>( fontImageData->data() ), font->AtlasSize.width, font->AtlasSize.height, 0, 1, nullptr ) )
	{
		logWARNING( "failed to initialize font" );
		return( nullptr );
	}
	
	auto fontFileBuffer = m_filesystem.LoadFileToBuffer( path );
	
	if( !fontFileBuffer.empty() )
	{
		stbtt_PackSetOversampling( &context, 2, 2 );

		auto glyphs = glyphRange.ToVector();
		
		u32 i = 0;
		for( const auto &glyph : glyphs )
		{
			font->m_codepoints[ glyph ] = i;
			i++;
		}
		
		font->m_packedChars = std::make_unique<stbtt_packedchar[]>( glyphs.size() );
		
		stbtt_pack_range range;
		range.first_unicode_codepoint_in_range = 0;
		range.array_of_unicode_codepoints = glyphs.data();
		range.num_chars                   = glyphs.size();
		range.chardata_for_range          = font->m_packedChars.get();
		range.font_size                   = size;
		
		if( !stbtt_PackFontRanges( &context, reinterpret_cast<unsigned char*>( fontFileBuffer.data() ), 0, &range, 1 ) )
		{
			logWARNING( "failed to pack font" );
			return( nullptr );
		}

		stbtt_PackEnd( &context );
		
		const auto fontImage = std::make_shared<CImage>( font->AtlasSize, 8, font->AtlasSize.width, std::move( fontImageData ) );
		
		if( !font->Texture )
		{
			font->Texture = std::make_shared<CTexture>();
		}
		
		CTextureLoader::FromImage( font->Texture, fontImage );
		
		return( font );
	}
	else
	{
		logWARNING( "failed to load font file '{0}'", path.generic_string() );
		return( nullptr );
	}
}

const std::shared_ptr<CFont> CFontBuilder::FromDummy() const
{
	// TODO
	// TODO create pink texture?
	THROW_STYX_EXCEPTION( "not implemented yet" );
}
