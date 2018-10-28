#pragma once

#include <vector>

#include "src/engine/renderer/model/CMesh.hpp"

// TODO fill it with functionality
class CModel
{
friend class CModelLoader;

public:
	CModel();
	~CModel();

private:
	std::vector< CMesh > m_meshes;
};
