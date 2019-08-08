#pragma once

#include <vector>

#include "src/renderer/model/CMesh.hpp"

// TODO fill it with functionality
class CModel final
{
private:
	CModel( const CModel& rhs );
	CModel & operator = ( const CModel& rhs );

public:
	CModel();
	~CModel();

	void Reset();

	std::vector<CMesh> Meshes;
};
