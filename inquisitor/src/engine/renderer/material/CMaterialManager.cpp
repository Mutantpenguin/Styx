#include "CMaterialManager.hpp"

#include "src/engine/logger/CLogger.hpp"

#include "CMaterialLoader.hpp"

CMaterialManager::CMaterialManager( const CSettings &settings, const CFileSystem &filesystem, const CSamplerManager &samplerManager, const CRendererCapabilities &rendererCapabilities )
	try :
		m_filesystem { filesystem },
		m_samplerManager { samplerManager },
		m_shaderManager( filesystem ),
		m_textureManager( settings, filesystem, rendererCapabilities ),
		m_dummyMaterial { CMaterialLoader::CreateDummyMaterial( m_shaderManager ) }
{
	if( nullptr == m_dummyMaterial )
	{
		logERROR( "dummy-material couldn't be generated" );
		throw Exception();
	}
}
catch( CTextureManager::Exception &e )
{
	logERROR( "unable to initialize TextureManager" );
	throw Exception();
}
catch( CShaderManager::Exception &e )
{
	logERROR( "unable to initialize ShaderManager" );
	throw Exception();
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

void CMaterialManager::Update( void )
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
			mtemp = CMaterialLoader::CreateMaterialFromFile( m_textureManager, m_shaderManager, m_samplerManager, m_filesystem, path );
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
