#include "CMaterialManager.hpp"

#include "src/engine/logger/CLogger.hpp"

#include "CMaterialLoader.hpp"

CMaterialManager::CMaterialManager( const CSettings &settings, const CFileSystem &filesystem, const CSamplerManager &samplerManager ) :
	m_filesystem { filesystem },
	m_samplerManager { samplerManager },
	m_shaderManager( filesystem ),
	m_textureManager( settings, filesystem )
{
}

CMaterialManager::~CMaterialManager( void )
{
	if( m_materials.size() > 0 )
	{
		logWARNING( "there are still '{0}' existing materials", m_materials.size() );
		#ifdef INQ_DEBUG
		for( auto material : m_materials )
		{
			logDEBUG( "  {0}", material.first );
		}
		#endif
	}
}

bool CMaterialManager::Init( const CRendererCapabilities &rendererCapabilities )
{
	if( !m_textureManager.Init( rendererCapabilities ) )
	{
		logERROR( "unable to initialize TextureManager" );
		return( false );
	}

	if( !m_shaderManager.Init() )
	{
		logERROR( "unable to initialize ShaderManager" );
		return( false );
	}

	m_dummyMaterial = CMaterialLoader::CreateDummyMaterial( m_shaderManager );

	return( true );
}

void CMaterialManager::Update( const float delta )
{
	for( auto it = std::cbegin( m_materials ); it != std::cend( m_materials ); )
	{
		if( (*it).second.unique() )
		{
			m_materials.erase( it++ );
		}
		else
		{
			++it;
		}
	}

	m_textureManager.Update();
}

/** Returns a handle to a material. It gets loaded if its not already loaded.
	@param[in]	path	The path to the Material.
	@return				Returns the material-handle.
*/
std::shared_ptr< CMaterial > CMaterialManager::LoadMaterial( const std::string &path )
{
	// search if we already loaded the material
	auto it = m_materials.find( path );
	if( m_materials.end() != it )
	{
		return( it->second );
	}

	std::shared_ptr< CMaterial > mtemp = nullptr;

	if( !m_filesystem.Exists( path ) )
	{
		logWARNING( "'{0}' does not exist", path );
	}
	else
	{
		if( path.substr( path.length()-4, 4 ) == std::string( ".mat" ) )
		{
			mtemp = CMaterialLoader::CreateMaterial( m_textureManager, m_shaderManager, m_samplerManager, path, m_filesystem.LoadTextFileToBuffer( path ) );
		}
		else
		{
			logWARNING( "file is not a material: '{0}'", path );
		}
	}

	if( mtemp )
	{
		m_materials[ path ] = mtemp;
		return( mtemp );
	}
	else
	{
		logWARNING( "failed to create material from file '{0}'", path );
		return( m_dummyMaterial );
	}
}

CShaderManager &CMaterialManager::ShaderManager( void )
{
	return( m_shaderManager );
}
