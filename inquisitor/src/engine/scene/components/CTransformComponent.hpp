#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

struct CTransformComponent
{
	glm::vec3	position	{ 0.0f, 0.0f, 0.0f };
	glm::quat	orientation	{ 1.0f, 0.0f, 0.0f, 0.0f };
	glm::vec3	scale		{ 1.0f, 1.0f, 1.0f };
};

#endif // TRANSFORMCOMPONENT_HPP
