#include "CFontLoader.hpp"

#include "src/logger/CLogger.hpp"

#include "src/core/FileExtension.hpp"

#include "external/stb/stb_truetype.h"

CFontLoader::CFontLoader( const CFileSystem &p_filesystem ) :
	m_filesystem { p_filesystem }
{
	logINFO( "font loader was initialized" );
}

CFontLoader::~CFontLoader()
{
	logINFO( "font loader is shutting down" );
}

void CFontLoader::FromFile( const std::shared_ptr<CFont> &font, const fs::path &path ) const
{
	if( !path.has_filename() )
	{
		logWARNING( "path '{0}' does not containt a filename", path.generic_string() );
		FromDummy( font );
	}

	const std::string fileExtensionString = path.extension().generic_string();

	if( fileExtensionString != FileExtension::Font::ttf )
	{
		logWARNING( "file type '{0}' of font file '{1}' is not supported", fileExtensionString, path.generic_string() );
		FromDummy( font );
	}
	else if( !m_filesystem.Exists( path ) )
	{
		logWARNING( "font file '{0}' does not exist", path.generic_string() );
		FromDummy( font );
	}
	else
	{
		if( !FromTtfFile( font, path ) )
		{
			FromDummy( font );
		}
	}
	
}

bool CFontLoader::FromTtfFile( const std::shared_ptr<CFont> &font, const fs::path &path ) const
{
	// TODO
}

void CFontLoader::FromDummy( const std::shared_ptr<CFont> &font ) const
{
	// TODO
	// TODO create pink texture?
}
