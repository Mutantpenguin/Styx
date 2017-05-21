#ifndef CMODEL_HPP
#define CMODEL_HPP

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

#endif // CMODEL_HPP
