#include "CMaterialManager.hpp"

#include "src/engine/logger/CLogger.hpp"

CMaterialManager::CMaterialManager( const CSettings &settings, const CFileSystem &filesystem, const CSamplerManager &samplerManager, const COpenGlAdapter &openGlAdapter )
	try :
		m_filesystem { filesystem },
		m_samplerManager { samplerManager },
		m_shaderManager( filesystem ),
		m_textureManager( settings, filesystem, openGlAdapter ),
		m_materialloader( filesystem, m_textureManager, m_shaderManager, m_samplerManager ),
		m_dummyMaterial { m_materialloader.CreateDummyMaterial() }
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
	if( !m_materials.empty() )
	{
		logWARNING( "there are still '{0}' existing materials", m_materials.size() );
		#ifdef INQ_DEBUG
		for( const auto material : m_materials )
		{
			logDEBUG( "\t{0}", material.first );
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
			logDEBUG( "erasing material: {0}", (*it).first );
			m_materials.erase( it++ );
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
	auto it = m_materials.find( path );
	if( m_materials.end() != it )
	{
		return( it->second );
	}

	auto temp = m_materialloader.CreateMaterialFromFile( path );

	if( temp )
	{
		m_materials[ path ] = temp;
		return( temp );
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
