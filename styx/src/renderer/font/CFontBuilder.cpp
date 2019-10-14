#include "CFontBuilder.hpp"

#include <array>

#include "external/stb/stb_truetype.h"

#include "src/core/StyxException.hpp"

#include "src/logger/CLogger.hpp"

#include "src/helper/image/CImage.hpp"

#include "src/core/FileExtension.hpp"

#include "src/renderer/texture/CTextureLoader.hpp"

const std::shared_ptr<const CFont> CFontBuilder::FromFile( const std::string &name, const fs::path &pathRegular, const u16 size, const CGlyphRange &glyphRange ) const
{
	return( FromFile( name, pathRegular, {}, size, glyphRange ) );
}

const std::shared_ptr<const CFont> CFontBuilder::FromFile( const std::string &name, const fs::path &pathRegular, const fs::path &pathBold, const u16 size, const CGlyphRange &glyphRange ) const
{
	if( glyphRange.Count() == 0 )
	{
		logWARNING( "glyph range contains 0 entries for font '{0}'", name );
		return( FromDummy( size ) );
	}

	if( !pathRegular.has_filename() )
	{
		logWARNING( "path '{0}' does not containt a filename", pathRegular.generic_string() );
		return( FromDummy( size ) );
	}

	const std::string fileExtensionString = pathRegular.extension().generic_string();

	if( fileExtensionString != FileExtension::Font::ttf )
	{
		logWARNING( "file type '{0}' of font file '{1}' is not supported", fileExtensionString, pathRegular.generic_string() );
		return( FromDummy( size ) );
	}
	else if( !m_filesystem.Exists( pathRegular ) )
	{
		logWARNING( "font file '{0}' does not exist", pathRegular.generic_string() );
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

		auto fontFileBufferRegular = m_filesystem.LoadFileToBuffer( pathRegular );

		if( !fontFileBufferRegular.empty() )
		{
			auto glyphs = glyphRange.ToVector();

			if( !PackFont( context, font->Size, glyphs, fontFileBufferRegular, font->CodepointsRegular ) )
			{
				logWARNING( "failed to pack regular font" );
				return( FromDummy( size ) );
			}

			if( !pathBold.empty() )
			{
				auto fontFileBufferBold = m_filesystem.LoadFileToBuffer( pathBold );

				if( !fontFileBufferBold.empty() )
				{
					auto &codepoints = font->CodepointsBold.emplace();

					if( !PackFont( context, font->Size, glyphs, fontFileBufferBold, codepoints ) )
					{
						logWARNING( "failed to pack bold font" );
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
			logWARNING( "failed to load font file '{0}'", pathRegular.generic_string() );
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

bool CFontBuilder::PackFont( stbtt_pack_context &context, const f16 size, std::vector<s32> &glyphs, CFileSystem::FileBuffer &fileBuffer, CFont::CodepointMap &codepointMap ) const
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
