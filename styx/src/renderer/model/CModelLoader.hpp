#pragma once

#include <string>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "src/system/CFileSystem.hpp"

#include "src/resource/CResources.hpp"

#include "src/renderer/model/CModel.hpp"

// TODO fill it with functionality
class CModelLoader
{
private:
	CModelLoader(const CModelLoader& rhs);
	CModelLoader& operator=(const CModelLoader& rhs);

public:
	explicit CModelLoader( const CFileSystem &p_filesystem, CResources &resources );
	~CModelLoader();

	void FromFile( const std::shared_ptr< CModel > &model, const fs::path &path ) const;

private:
	const CFileSystem &m_filesystem;

	CResources &m_resources;

	bool FromDaeFile( const std::shared_ptr< CModel > &model, const fs::path &path ) const;

	bool FromAssimpScene( const std::shared_ptr< CModel > &model, const aiScene *assimpScene ) const;

	bool ProcessMesh( const std::shared_ptr< CModel > &model, const aiMesh *assimpMesh ) const;

	void ProcessIndices( std::vector<u32> &indices, const aiMesh *assimpMesh ) const;

	void FromDummy( const std::shared_ptr< CModel > &model ) const;
};
