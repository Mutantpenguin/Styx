#pragma once

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
	explicit CModelLoader( const CFileSystem &p_filesystem );
	~CModelLoader();

	void FromFile( const std::shared_ptr< CModel > &model, const std::string &path ) const;

private:
	const CFileSystem &m_filesystem;

	void ProcessNode( const std::shared_ptr< CModel > &model, const aiNode *node, const aiScene *scene ) const;

	void ProcessMesh( const std::shared_ptr< CModel > &model, const aiMesh *mesh, const aiScene *scene ) const;

	void FromDummy( const std::shared_ptr< CModel > &model ) const;
};
