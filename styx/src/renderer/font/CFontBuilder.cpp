#include "CFontBuilder.hpp"

#include <array>

#include "external/stb/stb_truetype.h"

#include "src/core/StyxException.hpp"

#include "src/logger/CLogger.hpp"

#include "src/helper/image/CImage.hpp"

#include "src/core/FileExtension.hpp"

#include "src/renderer/texture/CTextureLoader.hpp"

const std::shared_ptr<const CFont> CFontBuilder::FromFile( const std::string &name, const fs::path &pathRegularStyle, const u16 size, const CGlyphRange &glyphRange ) const
{
	return( FromFile( name, pathRegularStyle, {}, size, glyphRange ) );
}

const std::shared_ptr<const CFont> CFontBuilder::FromFile( const std::string &name, const fs::path &pathRegularStyle, const fs::path &pathBoldStyle, const u16 size, const CGlyphRange &glyphRange ) const
{
	if( glyphRange.Count() == 0 )
	{
		logWARNING( "glyph range contains 0 entries for font '{0}'", name );
		return( FromDummy( size ) );
	}

	if( !pathRegularStyle.has_filename() )
	{
		logWARNING( "path '{0}' does not containt a filename", pathRegularStyle.generic_string() );
		return( FromDummy( size ) );
	}

	const std::string fileExtensionString = pathRegularStyle.extension().generic_string();

	if( fileExtensionString != FileExtension::Font::ttf )
	{
		logWARNING( "file type '{0}' of font file '{1}' is not supported", fileExtensionString, pathRegularStyle.generic_string() );
		return( FromDummy( size ) );
	}
	else if( !m_filesystem.Exists( pathRegularStyle ) )
	{
		logWARNING( "font file '{0}' does not exist", pathRegularStyle.generic_string() );
		return( FromDummy( size ) );
	}
	else
	{
		// TODO really define a fixed size for the Atlas here?
		auto font = std::make_shared<CFont>( name, size, CSize( 4096, 4096 ) );

		auto fontImageData = std::make_unique<CImage::PixelBuffer>( font->AtlasSize.width * font->AtlasSize.height );

		stbtt_pack_context context;
		if( !stbtt_PackBegin( &context, reinterpret_cast<unsigned char*>( fontImageData->data() ), font->AtlasSize.width, font->AtlasSize.height, 0, 1, nullptr ) )
		{
			logWARNING( "failed to initialize font" );
			return( FromDummy( size ) );
		}

		stbtt_PackSetOversampling( &context, 2, 2 );

		auto fontFileBufferRegularStyle = m_filesystem.LoadFileToBuffer( pathRegularStyle );

		if( !fontFileBufferRegularStyle.empty() )
		{
			auto glyphs = glyphRange.ToVector();

			if( !PackFont( context, font->Size, glyphs, fontFileBufferRegularStyle, font->CodepointsRegularStyle ) )
			{
				logWARNING( "failed to pack regular style font" );
				return( FromDummy( size ) );
			}

			if( !pathBoldStyle.empty() )
			{
				auto fontFileBufferBoldStyle = m_filesystem.LoadFileToBuffer( pathBoldStyle );

				if( !fontFileBufferBoldStyle.empty() )
				{
					auto &codepoints = font->CodepointsBoldStyle.emplace();

					if( !PackFont( context, font->Size, glyphs, fontFileBufferBoldStyle, codepoints ) )
					{
						logWARNING( "failed to pack bold style font" );
						return( FromDummy( size ) );
					}
				}
			}

			stbtt_PackEnd( &context );

			const auto fontImage = std::make_shared<CImage>( font->AtlasSize, 8, font->AtlasSize.width, std::move( fontImageData ) );

			CTextureLoader::FromImage( font->Texture, fontImage );

			return( font );
		}
		else
		{
			logWARNING( "failed to load font file '{0}'", pathRegularStyle.generic_string() );
			return( FromDummy( size ) );
		}

		
		return( font );
	}
	
}

const std::shared_ptr<const CFont> CFontBuilder::FromDummy( const u16 size ) const
{
	// creates a dummy font with absolutely no glyphs and a black 8x8 pixel texture

	auto font = std::make_shared<CFont>( "Dummy", size, CSize( 8, 8 ) );

	auto fontImageData = std::make_unique<CImage::PixelBuffer>( font->AtlasSize.width * font->AtlasSize.height );

	const auto fontImage = std::make_shared<CImage>( font->AtlasSize, 8, font->AtlasSize.width, std::move( fontImageData ) );

	CTextureLoader::FromImage( font->Texture, fontImage );

	return( font );
}

const bool CFontBuilder::PackFont( stbtt_pack_context &context, const f16 size, std::vector<i32> &glyphs, CFileSystem::FileBuffer &fileBuffer, CFont::CodepointMap &codepointMap ) const
{
	auto packedChars = std::make_unique<stbtt_packedchar[]>( glyphs.size() );

	stbtt_pack_range range;
	range.first_unicode_codepoint_in_range = 0;
	range.array_of_unicode_codepoints = glyphs.data();
	range.num_chars = glyphs.size();
	range.chardata_for_range = packedChars.get();
	range.font_size = size;

	if( !stbtt_PackFontRanges( &context, reinterpret_cast<unsigned char*>( fileBuffer.data() ), 0, &range, 1 ) )
	{
		return( false );
	}

	// copy over the packed chars into our own map for the codepoints
	u32 i = 0;
	for( const auto &glyph : glyphs )
	{
		codepointMap[ glyph ] = packedChars[ i ];
		i++;
	}

	return( true );
}
