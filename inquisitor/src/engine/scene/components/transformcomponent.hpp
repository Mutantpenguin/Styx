#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

struct TransformComponent
{
  glm::vec3	position;
  glm::quat	orientation;
  float		scale;
};

#endif // TRANSFORMCOMPONENT_HPP
