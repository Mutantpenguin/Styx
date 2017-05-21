#ifndef CMODELLOADER_HPP
#define CMODELLOADER_HPP

#include <string>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "src/engine/system/CFileSystem.hpp"

#include "src/engine/renderer/model/CModel.hpp"

// TODO fill it with functionality
class CModelLoader
{
private:
	CModelLoader(const CModelLoader& rhs);
	CModelLoader& operator=(const CModelLoader& rhs);

public:
	CModelLoader( const CFileSystem &p_filesystem );
	~CModelLoader();

	void FromFile( const std::string &path, std::shared_ptr< CModel > &model ) const;

private:
	const CFileSystem &m_filesystem;

	void ProcessNode( const aiNode *node, const aiScene *scene, std::shared_ptr< CModel > &model ) const;

	void ProcessMesh( const aiMesh *mesh, const aiScene *scene, std::shared_ptr< CModel > &model ) const;

	void FromDummy( std::shared_ptr< CModel > &model ) const;
};

#endif // CMODELLOADER_HPP
