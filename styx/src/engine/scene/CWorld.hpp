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
	static constexpr glm::vec3 Z	{ 0.0f, 0.0f, 1.0f };
	static constexpr glm::vec3 Y	{ 0.0f, 1.0f, 0.0f };
	static constexpr glm::vec3 X	{ 1.0f, 0.0f, 0.0f };
};
