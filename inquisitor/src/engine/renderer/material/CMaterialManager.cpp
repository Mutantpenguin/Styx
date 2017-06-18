#include "CMaterialManager.hpp"

#include "src/engine/logger/CLogger.hpp"

CMaterialManager::CMaterialManager( const CFileSystem &filesystem, CShaderManager &shaderManager )
	try :
		m_filesystem { filesystem },
		m_shaderManager { shaderManager },
		m_materialLoader( filesystem, m_shaderManager )
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
		for( const auto & [ filename, _ ] : m_materialFiles )
		{
			logDEBUG( "\t{0}", filename );
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
}

const std::shared_ptr< const CMaterial > CMaterialManager::LoadMaterial( const std::string &path )
{
	const auto it = m_materialFiles.find( path );
	if( std::end( m_materialFiles ) != it )
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
	logINFO( "reloading materials:" );

	for( auto & [ filename, materialFile ] : m_materialFiles )
	{
		const auto mtime = m_filesystem.GetLastModTime( filename );
		if( mtime > materialFile.mtime )
		{
			logINFO( "    {0}", filename );

			materialFile.material->Reset();

			m_materialLoader.FromFile( filename, materialFile.material );

			materialFile.mtime = mtime;
		}
	}
}

CShaderManager &CMaterialManager::ShaderManager( void )
{
	return( m_shaderManager );
}
