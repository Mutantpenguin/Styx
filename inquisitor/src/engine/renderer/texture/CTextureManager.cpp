#include "CTextureManager.hpp"

#ifdef WIN32
	#include <windows.h>
#endif

#include "src/engine/renderer/CGLState.hpp"

#include "src/engine/logger/CLogger.hpp"


CTextureManager::CTextureManager( const CSettings &p_settings, const CFileSystem &p_filesystem, const COpenGlAdapter &openGlAdapter ) :
	m_textureLoader( p_settings, p_filesystem, openGlAdapter )
{
}

CTextureManager::~CTextureManager( void )
{
	if( !m_textures.empty() )
	{
		logWARNING( "there are still '{0}' existing m_textures", m_textures.size() );
		#ifdef INQ_DEBUG
		for( const auto texture : m_textures )
		{
			logDEBUG( "\t{0}", texture.first );
		}
		#endif
	}
}

void CTextureManager::Update( void )
{
	for( auto it = std::cbegin( m_textures ); it != std::cend( m_textures ); )
	{
		if( it->second.unique() )
		{
			logDEBUG( "erasing texture: {0}", it->first );
			m_textures.erase( it++ );
		}
		else
		{
			++it;
		}
	}
}

std::shared_ptr< CTexture > CTextureManager::LoadTexture( const std::string &path )
{
	const auto it = m_textures.find( path );
	if( m_textures.end() != it )
	{
		return( it->second );
	}

	auto newTexture = std::make_shared< CTexture >();

	m_textureLoader.FromFile( path, newTexture );

	m_textures[ path ] = newTexture;

	return( newTexture );
}
