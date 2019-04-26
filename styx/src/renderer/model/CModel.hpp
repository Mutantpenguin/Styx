#pragma once

#include <vector>
#include <string>

#include "src/renderer/model/CMesh.hpp"

// TODO fill it with functionality
class CModel final
{
public:
	using ResourceIdType = std::string;

	static std::string IdToString( const ResourceIdType &id )
	{
		return( id );
	}

private:
	CModel( const CModel& rhs );
	CModel & operator = ( const CModel& rhs );

public:
	CModel();
	~CModel();

	void Reset();

	std::vector< CMesh > Meshes;
};
