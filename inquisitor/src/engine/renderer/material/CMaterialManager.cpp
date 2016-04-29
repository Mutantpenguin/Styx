#include "CMaterialManager.hpp"

#include "../../logger/CLogger.hpp"

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
		LOG( logWARNING ) << "there are still '" + std::to_string( m_materials.size() ) + "' existing materials";
		#ifdef INQ_DEBUG
		for( auto material : m_materials )
		{
			LOG( logDEBUG ) << "  " << material.first;
		}
		#endif
	}
}

bool CMaterialManager::Init( const CRendererCapabilities &rendererCapabilities )
{
	if( !m_textureManager.Init( rendererCapabilities ) )
	{
		LOG( logERROR ) << "unable to initialize TextureManager";
		return( false );
	}

	if( !m_shaderManager.Init() )
	{
		LOG( logERROR ) << "unable to initialize ShaderManager";
		return( false );
	}

	CreateDummyMaterial();

	return( true );
}

void CMaterialManager::Update( const float delta )
{
	for( auto it = m_materials.cbegin(); it != m_materials.cend(); )
	{
		auto material = (*it).second.lock();

		if( !material )
		{
			m_materials.erase( it++ );
		}
		else
		{
			material->Update( delta );

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
		return( it->second.lock() );
	}

	std::shared_ptr< CMaterial > mtemp = nullptr;

	if( !m_filesystem.Exists( path ) )
	{
		LOG( logWARNING ) << "'" << path << "' does not exist";
	}
	else
	{
		if( path.substr( path.length()-4, 4 ) == std::string( ".mat" ) )
		{
			mtemp = CMaterialLoader::CreateMaterial( m_textureManager, m_shaderManager, m_samplerManager, path, m_filesystem.LoadTextFileToBuffer( path ) );
		}
		else
		{
			LOG( logWARNING ) << "file is not a material: '" << path << "'";
		}
	}

	if( mtemp )
	{
		m_materials[ path ] = mtemp;
		return( mtemp );
	}
	else
	{
		LOG( logWARNING ) << "failed to create material from file '" << path << "'";
		return( m_dummyMaterial );
	}
}

void CMaterialManager::CreateDummyMaterial( void )
{
	m_dummyMaterial = std::make_shared< CMaterial >( "dummy" );

	std::shared_ptr< CMaterialLayer > layer = m_dummyMaterial->CreateLayer();

	layer->m_shader = m_shaderManager.GetDummyShader();
}

CShaderManager &CMaterialManager::ShaderManager( void )
{
	return( m_shaderManager );
}
