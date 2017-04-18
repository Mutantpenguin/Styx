#include "CMaterialManager.hpp"

#include "src/engine/logger/CLogger.hpp"

CMaterialManager::CMaterialManager( const CSettings &settings, const CFileSystem &filesystem, const CSamplerManager &samplerManager, const COpenGlAdapter &openGlAdapter )
	try :
		m_filesystem { filesystem },
		m_samplerManager { samplerManager },
		m_shaderManager( filesystem ),
		m_textureManager( settings, filesystem, openGlAdapter ),
		m_materialLoader( filesystem, m_textureManager, m_shaderManager, m_samplerManager )
{
}
catch( CShaderManager::Exception &e )
{
	logERROR( "unable to initialize ShaderManager" );
	throw Exception();
}

CMaterialManager::~CMaterialManager( void )
{
	if( !m_materialFiles.empty() )
	{
		logWARNING( "there are still '{0}' existing materials", m_materialFiles.size() );
		#ifdef INQ_DEBUG
		for( const auto material : m_materialFiles )
		{
			logDEBUG( "\t{0}", material.first );
		}
		#endif
	}
}

void CMaterialManager::Update( void )
{
	for( auto it = std::cbegin( m_materialFiles ); it != std::cend( m_materialFiles ); )
	{
		if( it->second.material.unique() )
		{
			m_materialFiles.erase( it++ );
		}
		else
		{
			++it;
		}
	}

	m_textureManager.Update();
}

std::shared_ptr< CMaterial > CMaterialManager::LoadMaterial( const std::string &path )
{
	const auto it = m_materialFiles.find( path );
	if( m_materialFiles.end() != it )
	{
		return( it->second.material );
	}

	auto newMaterial = std::make_shared< CMaterial >();

	m_materialLoader.FromFile( path, newMaterial );

	auto &materialFile = m_materialFiles[ path ];

	materialFile.material = newMaterial;
	materialFile.mtime    = m_filesystem.GetLastModTime( path );

	return( newMaterial );
}

void CMaterialManager::ReloadMaterials( void )
{
	m_textureManager.ReloadTextures();

	logINFO( "reloading materials:" );

	for( auto &materialFile : m_materialFiles )
	{
		const auto mtime = m_filesystem.GetLastModTime( materialFile.first );
		if( mtime > materialFile.second.mtime )
		{
			logINFO( "    {0}", materialFile.first );

			materialFile.second.material->Reset();

			m_materialLoader.FromFile( materialFile.first, materialFile.second.material );

			materialFile.second.mtime = mtime;
		}
	}
}

CShaderManager &CMaterialManager::ShaderManager( void )
{
	return( m_shaderManager );
}
