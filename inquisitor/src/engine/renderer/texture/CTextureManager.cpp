#include "CTextureManager.hpp"

#ifdef WIN32
	#include <windows.h>
#endif

#include "src/engine/renderer/CGLState.hpp"

#include "src/engine/logger/CLogger.hpp"


CTextureManager::CTextureManager( const CSettings &p_settings, const CFileSystem &p_filesystem, const COpenGlAdapter &openGlAdapter ) :
	m_filesystem { p_filesystem },
	m_textureLoader( p_settings, p_filesystem, openGlAdapter )
{
}

CTextureManager::~CTextureManager( void )
{
	if( !m_textureFiles.empty() )
	{
		logWARNING( "there are still '{0}' existing m_textures", m_textureFiles.size() );
		#ifdef INQ_DEBUG
		for( const auto texture : m_textureFiles )
		{
			logDEBUG( "\t{0}", texture.first );
		}
		#endif
	}
}

void CTextureManager::Update( void )
{
	for( auto it = std::cbegin( m_textureFiles ); it != std::cend( m_textureFiles ); )
	{
		if( it->second.texture.unique() )
		{
			m_textureFiles.erase( it++ );
		}
		else
		{
			++it;
		}
	}
}

std::shared_ptr< CTexture > CTextureManager::LoadTexture( const std::string &path )
{
	const auto it = m_textureFiles.find( path );
	if( m_textureFiles.end() != it )
	{
		return( it->second.texture );
	}

	auto newTexture = std::make_shared< CTexture >();

	m_textureLoader.FromFile( path, newTexture );

	auto &textureFile = m_textureFiles[ path ];

	textureFile.texture = newTexture;
	textureFile.mtime   = m_filesystem.GetLastModTime( path );

	return( newTexture );
}

void CTextureManager::ReloadTextures( void )
{
	logINFO( "reloading textures:" );

	for( auto &textureFile : m_textureFiles )
	{
		const auto mtime = m_filesystem.GetLastModTime( textureFile.first );
		if( mtime > textureFile.second.mtime )
		{
			logINFO( "    {0}", textureFile.first );

			textureFile.second.texture->Reset();

			m_textureLoader.FromFile( textureFile.first, textureFile.second.texture );

			textureFile.second.mtime = mtime;
		}
	}
}
