#include "CModelLoader.hpp"

#include "src/logger/CLogger.hpp"

#include "src/geometry/Geometry.hpp"
#include "src/geometry/Vertex.hpp"

CModelLoader::CModelLoader( const CFileSystem &p_filesystem, CResourceCacheManager &resourceCacheManager ) :
	m_filesystem { p_filesystem },
	m_resourceCacheManager { resourceCacheManager }
{
	logINFO( "model loader was initialized" );
}

CModelLoader::~CModelLoader()
{
	logINFO( "model loader is shutting down" );
}

void CModelLoader::FromFile( const std::shared_ptr< CModel > &model, const fs::path &path ) const
{
	if( !path.has_filename() )
	{
		logWARNING( "path '{0}' does not containt a filename", path.generic_string() );
		FromDummy( model );
	}

	if( !m_filesystem.Exists( path ) )
	{
		logWARNING( "'{0}' does not exist", path.generic_string() );
		FromDummy( model );
	}
	else
	{
		const std::string fileExtensionString = path.extension().generic_string();

		if( std::string( ".dae" ) == fileExtensionString )
		{
			if( !FromDaeFile( model, path ) )
			{
				FromDummy( model );
			}
		}
		else
		{
			logWARNING( "file extension '{0}' not implemented yet", fileExtensionString );
			FromDummy( model );
		}
	}
}

bool CModelLoader::FromDaeFile( const std::shared_ptr< CModel > &model, const fs::path &path ) const
{
	const auto buffer = m_filesystem.LoadFileToBuffer( path );

	Assimp::Importer importer;

	const aiScene *scene = importer.ReadFileFromMemory( buffer.data(), buffer.size(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace, nullptr );

	if( !scene || ( scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ) || !scene->mRootNode )
	{
		logWARNING( "failed to load '{0}' because of: {1}", path.generic_string(), importer.GetErrorString() );
		return( false );
	}

	ProcessNode( model, scene->mRootNode, scene );

	return( true );
}

void CModelLoader::ProcessNode( const std::shared_ptr< CModel > &model, const aiNode *node, const aiScene *scene ) const
{
    // Process all the node's meshes (if any)
    for( GLuint i = 0; i < node->mNumMeshes; i++ )
    {
        aiMesh* mesh = scene->mMeshes[ node->mMeshes[ i ] ];
        ProcessMesh( model, mesh, scene );
    }

    // Then do the same for each of its children
    for( GLuint i = 0; i < node->mNumChildren; i++ )
    {
        ProcessNode( model, node->mChildren[ i ], scene );
    }
}

void CModelLoader::ProcessMesh( const std::shared_ptr< CModel > &model, const aiMesh *mesh, const aiScene *scene ) const
{
	if( mesh->mMaterialIndex >= 0 )
	{
		/* TODO aiTextureType_DIFFUSE
		for( unsigned int i = 0; i < mat->GetTextureCount( type ); i++ )
		{
		 * */
	}


	// TODO mesh->HasNormals
	
	if( mesh->HasTextureCoords( 0 ) )
	{
		if( mesh->HasTangentsAndBitangents() )
		{
			Geometry<VertexPNTBU0> geometry;
			// TODO implement
			throw new std::logic_error( "not yet implemented" );
		}
		else
		{
			Geometry<VertexPNU0> geometry;

			for( unsigned int i = 0; i < mesh->mNumVertices; i++ )
			{
				VertexPNU0 vertex;

				vertex.Position = { mesh->mVertices[ i ].x, mesh->mVertices[ i ].y, mesh->mVertices[ i ].z };
				vertex.Normal = { mesh->mNormals[ i ].x, mesh->mNormals[ i ].y, mesh->mNormals[ i ].z };
				vertex.UV0 = { mesh->mTextureCoords[ 0 ][ i ].x, mesh->mTextureCoords[ 0 ][ i ].y };

				geometry.Vertices.emplace_back( vertex );
			}

			// TODO model->Meshes.emplace_back( CMesh( GL_TRIANGLES, geometry,  );
			throw new std::logic_error( "not yet implemented" );
		}
	}
	else
	{
		if( mesh->HasTangentsAndBitangents() )
		{
			// Geometry<VertexPNTB> geometry;
			// TODO implement
			throw new std::logic_error( "not yet implemented" );
		}
		else
		{
			Geometry<VertexPN> geometry;

			for( unsigned int i = 0; i < mesh->mNumVertices; i++ )
			{
				VertexPN vertex;

				vertex.Position = { mesh->mVertices[ i ].x, mesh->mVertices[ i ].y, mesh->mVertices[ i ].z };
				vertex.Normal = { mesh->mNormals[ i ].x, mesh->mNormals[ i ].y, mesh->mNormals[ i ].z };

				geometry.Vertices.emplace_back( vertex );
			}
			// TODO implement
			throw new std::logic_error( "not yet implemented" );
		}
	}

	for( unsigned int i = 0; i < mesh->mNumVertices; i++ )
	{
		/* TODO change to new Geometry structs
		Primitives::SVertex vertex;

		vertex.Position = { mesh->mVertices[ i ].x, mesh->mVertices[ i ].y, mesh->mVertices[ i ].z };

		vertex.Normal = { mesh->mNormals[ i ].x, mesh->mNormals[ i ].y, mesh->mNormals[ i ].z };

		if( mesh->mTextureCoords[ 0 ] )
		{
			vertex.TexCoord = { mesh->mTextureCoords[ 0 ][ i ].x, mesh->mTextureCoords[ 0 ][ i ].y };
		}
		*/

		/* TODO Tangents
		vertex.Tangent = { mesh->mTangents[ i ].x, mesh->mTangents[ i ].y, mesh->mTangents[ i ].z };

		vertex.Bitangent = { mesh->mBitangents[ i ].x, mesh->mBitangents[ i ].y, mesh->mBitangents[ i ].z };
		*/
	}


	/*


	// TODO do the work

	model->m_meshes.emplace_back( mesh );
	 * */
}

void CModelLoader::FromDummy( const std::shared_ptr< CModel > &model ) const
{
	// TODO implement
	logERROR( "not implemented yet" );
	throw new std::logic_error( "Function not yet implemented" );
}
