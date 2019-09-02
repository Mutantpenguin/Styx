#include "CFontBuilder.hpp"

#include <array>

#include "external/stb/stb_truetype.h"

#include "src/logger/CLogger.hpp"

#include "src/helper/image/CImage.hpp"

#include "src/core/FileExtension.hpp"

#include "src/renderer/texture/CTextureLoader.hpp"


CFontBuilder::CFontBuilder( const CFileSystem &p_filesystem ) :
	m_filesystem { p_filesystem }
{
	logINFO( "font loader was initialized" );
}

CFontBuilder::~CFontBuilder()
{
	logINFO( "font loader is shutting down" );
}

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
	// TODO
	
	auto font = std::make_shared<CFont>();
	
	font->Size = size;
	
	font->AtlasSize = { 4096, 4096 };
	//font->AtlasSize = { 512, 512 };
	
	auto fontImageData = std::make_unique<CImage::PixelBuffer>( font->AtlasSize.width * font->AtlasSize.height );
	
	stbtt_pack_context context;
	if( !stbtt_PackBegin( &context, reinterpret_cast<unsigned char*>( fontImageData->data() ), font->AtlasSize.width, font->AtlasSize.height, 0, 1, nullptr ) )
	{
		logWARNING( "Failed to initialize font" );
		return( nullptr );
	}
	
	auto fontFile = m_filesystem.LoadFileToBuffer( path );
	
	stbtt_PackSetOversampling( &context, 2, 2 );

	//const auto firstChar = 0xf000;
	//const auto countChar = 0xf897 - firstChar;

	
	auto glyphs = glyphRange.ToVector();
	
	auto charInfo = std::make_unique<stbtt_packedchar[]>( glyphs.size() );
	
	stbtt_pack_range range;
	range.first_unicode_codepoint_in_range = 0;
	range.array_of_unicode_codepoints = glyphs.data();
	range.num_chars                   = glyphs.size();
	range.chardata_for_range          = charInfo.get();
	range.font_size                   = size;
	
	if( !stbtt_PackFontRanges( &context, reinterpret_cast<unsigned char*>( fontFile.data() ), 0, &range, 1 ) )
	{
		logWARNING( "Failed to pack font" );
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

const std::shared_ptr<CFont> CFontBuilder::FromDummy() const
{
	// TODO
	// TODO create pink texture?
}
