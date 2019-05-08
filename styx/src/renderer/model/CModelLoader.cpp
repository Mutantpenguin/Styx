#include "CModelLoader.hpp"

#include "src/logger/CLogger.hpp"

#include "src/renderer/geometry/Geometry.hpp"
#include "src/renderer/geometry/Vertex.hpp"

CModelLoader::CModelLoader( const CFileSystem &p_filesystem, CResources &resources ) :
	m_filesystem { p_filesystem },
	m_resources { resources }
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

	const aiScene *assimpScene = importer.ReadFileFromMemory( buffer.data(), buffer.size(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace, nullptr );

	if( !assimpScene || ( assimpScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ) || !assimpScene->mRootNode )
	{
		logWARNING( "failed to load '{0}' because of: {1}", path.generic_string(), importer.GetErrorString() );
		return( false );
	}

	FromAssimpScene( model, assimpScene );

	return( true );
}

bool CModelLoader::FromAssimpScene( const std::shared_ptr< CModel > &model, const aiScene *assimpScene ) const
{
	model->Meshes.reserve( assimpScene->mNumMeshes );

	for( unsigned int i = 0; i < model->Meshes.size(); i++ )
    {
		if( !ProcessMesh( model, assimpScene->mMeshes[ i ] ) )
		{
			return( false );
		}
    }

	return( true );
}

bool CModelLoader::ProcessMesh( const std::shared_ptr< CModel > &model, const aiMesh *assimpMesh ) const
{
	if( assimpMesh->mMaterialIndex >= 0 )
	{
		/* TODO aiTextureType_DIFFUSE
		for( unsigned int i = 0; i < mat->GetTextureCount( type ); i++ )
		{
		 * */
	}

	if( !assimpMesh->HasPositions() )
	{
		logWARNING( "mesh has no positions" );
		return( false );
	}

	const auto &assimpVertices = assimpMesh->mVertices;
	const auto &assimpNormals = assimpMesh->mNormals;
	const auto &assimpTextureCoords = assimpMesh->mTextureCoords;
	const auto &assimpTangents = assimpMesh->mTangents;
	const auto &assimpBitangents = assimpMesh->mBitangents;

	// TODO mesh->HasNormals

	if( assimpMesh->HasTextureCoords( 0 ) )
	{
		if( assimpMesh->HasTangentsAndBitangents() )
		{
			Geometry<VertexPNTBU0> geometry;
			// TODO implement
			/* TODO Tangents
			vertex.Tangent = { assimpTangents[ i ].x, assimpTangents[ i ].y, assimpTangents[ i ].z };
			vertex.Bitangent = { assimpBitangents[ i ].x, assimpBitangents[ i ].y, assimpBitangents[ i ].z };
			*/
			throw new std::logic_error( "not yet implemented" );
		}
		else
		{
			Geometry<VertexPNU0> geometry;

			for( unsigned int i = 0; i < assimpMesh->mNumVertices; i++ )
			{
				VertexPNU0 vertex;

				vertex.Position = { assimpVertices[ i ].x, assimpVertices[ i ].y, assimpVertices[ i ].z };
				vertex.Normal = { assimpNormals[ i ].x, assimpNormals[ i ].y, assimpNormals[ i ].z };
				vertex.UV0 = { assimpTextureCoords[ 0 ][ i ].x, assimpTextureCoords[ 0 ][ i ].y };

				geometry.Vertices.emplace_back( vertex );
			}

			// TODO model->Meshes.emplace_back( CMesh( geometry,  );
			throw new std::logic_error( "not yet implemented" );
		}
	}
	else
	{
		if( assimpMesh->HasTangentsAndBitangents() )
		{
			 Geometry<VertexPNTB> geometry;
			// TODO implement
			/* TODO Tangents
			vertex.Tangent = { assimpTangents[ i ].x, assimpTangents[ i ].y, assimpTangents[ i ].z };
			vertex.Bitangent = { assimpBitangents[ i ].x, assimpBitangents[ i ].y, assimpBitangents[ i ].z };
			*/
			throw new std::logic_error( "not yet implemented" );
		}
		else
		{
			Geometry<VertexPN> geometry;

			geometry.Mode = GL_TRIANGLES;

			for( unsigned int i = 0; i < assimpMesh->mNumVertices; i++ )
			{
				VertexPN vertex;

				vertex.Position = { assimpVertices[ i ].x, assimpVertices[ i ].y, assimpVertices[ i ].z };
				vertex.Normal = { assimpNormals[ i ].x, assimpNormals[ i ].y, assimpNormals[ i ].z };

				geometry.Vertices.emplace_back( vertex );
			}
			// TODO implement

			ProcessIndices( geometry.Indices, assimpMesh );			

			// TODO model->Meshes.emplace_back( CMesh( geometry))
		}
	}

	return( true );
}

void CModelLoader::ProcessIndices( std::vector<u32> &indices, const aiMesh *assimpMesh ) const
{
	for( unsigned int i = 0; i < assimpMesh->mNumFaces; i++ )
	{
		const aiFace &face = assimpMesh->mFaces[ i ];
		for( unsigned int j = 0; j < face.mNumIndices; j++ )
		{
			indices.push_back( face.mIndices[ j ] );
		}
	}
}

void CModelLoader::FromDummy( const std::shared_ptr< CModel > &model ) const
{
	// TODO implement
	logERROR( "not implemented yet" );
	throw new std::logic_error( "Function not yet implemented" );
}
