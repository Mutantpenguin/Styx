#include "CModelLoader.hpp"

#include "src/logger/CLogger.hpp"

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

void CModelLoader::FromFile( const std::shared_ptr< CModel > &model, const std::string &path ) const
{
	if( !m_filesystem.Exists( path ) )
	{
		logWARNING( "'{0}' does not exist", path );
		FromDummy( model );
	}

	const auto buffer = m_filesystem.LoadFileToBuffer( path );

	Assimp::Importer importer;

	const aiScene *scene = importer.ReadFileFromMemory( buffer.data(), buffer.size(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace, nullptr );

	if( !scene || ( scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ) || !scene->mRootNode )
    {
        logWARNING( "failed to load '{0}' because of: {1}", path, importer.GetErrorString() );
        FromDummy( model );
    }

	ProcessNode( model, scene->mRootNode, scene );
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
	//CMesh mesh(

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
	logERROR( "not implemented yet" );
	throw new std::logic_error( "Function not yet implemented" );
}
