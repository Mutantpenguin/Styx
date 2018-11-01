#pragma once

#include <glm/glm.hpp>

class CWorld final
{
private:
	CWorld() = delete;
	~CWorld() = delete;
	CWorld( const CWorld& rhs ) = delete;
	CWorld& operator=( const CWorld& rhs ) = delete;

public:
	static const glm::vec3 Z;
	static const glm::vec3 Y;
	static const glm::vec3 X;
};
