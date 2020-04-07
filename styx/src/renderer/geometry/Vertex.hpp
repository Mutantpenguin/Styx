#pragma once

#include <glm/glm.hpp>

struct VertexP final
{
	glm::vec3 Position;
};

struct VertexPN final
{
	glm::vec3 Position;
	glm::vec3 Normal;
};

struct VertexPC final
{
	glm::vec3 Position;
	glm::vec3 Color;
};

struct VertexPU0 final
{
	glm::vec3 Position;
	glm::vec2 UV0;
};

struct VertexPCU0 final
{
	glm::vec3 Position;
	glm::vec3 Color;
	glm::vec2 UV0;
};

struct VertexPNU0 final
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 UV0;
};

struct VertexPNCU0 final
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 Color;
	glm::vec2 UV0;
};

struct VertexPNTB final
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

struct VertexPNTBU0 final
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
	glm::vec2 UV0;
};

struct VertexPNTBCU0U1U2U3 final
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
	glm::vec3 Color;
	glm::vec2 UV0;
	glm::vec2 UV1;
	glm::vec2 UV2;
	glm::vec2 UV3;
};