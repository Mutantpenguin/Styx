#include "CModelLoader.hpp"

#include "src/engine/logger/CLogger.hpp"

CModelLoader::CModelLoader( const CFileSystem &p_filesystem ) :
	m_filesystem { p_filesystem }
{
}

CModelLoader::~CModelLoader()
{
}

void CModelLoader::FromFile( const std::string &path, std::shared_ptr< CModel > &model ) const
{
	if( !m_filesystem.Exists( path ) )
	{
		logWARNING( "'{0}' does not exist", path );
		FromDummy( model );
	}

	const auto buffer = m_filesystem.LoadFileToBuffer( path );

	Assimp::Importer importer;

	const aiScene *scene = importer.ReadFileFromMemory( buffer.data(), buffer.size(), aiProcess_Triangulate | aiProcess_FlipUVs, nullptr );

	if( !scene || ( scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ) || !scene->mRootNode )
    {
        logWARNING( "failed to load '{0}' because of: {1}", path, importer.GetErrorString() );
        FromDummy( model );
    }

	/*TODO
    this->directory = path.substr(0, path.find_last_of('/'));

    this->processNode(scene->mRootNode, scene);
	 * */
}

void CModelLoader::ProcessNode( const aiNode *node, const aiScene *scene, std::shared_ptr< CModel > &model ) const
{
    // Process all the node's meshes (if any)
    for( GLuint i = 0; i < node->mNumMeshes; i++ )
    {
        aiMesh* mesh = scene->mMeshes[ node->mMeshes[ i ] ];
        ProcessMesh( mesh, scene, model );
    }
    // Then do the same for each of its children
    for( GLuint i = 0; i < node->mNumChildren; i++ )
    {
        ProcessNode( node->mChildren[ i ], scene, model );
    }
}

void CModelLoader::ProcessMesh( const aiMesh *mesh, const aiScene *scene, std::shared_ptr< CModel > &model ) const
{
	// TODO
	//model->m_meshes.emplace_back( )
}

void CModelLoader::FromDummy( std::shared_ptr< CModel > &model ) const
{
	logERROR( "not implemented yet" );
	throw new std::logic_error( "Function not yet implemented" );
}
