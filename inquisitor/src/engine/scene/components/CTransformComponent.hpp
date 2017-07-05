#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class CTransformComponent final
{
public:
	void Position( const glm::vec3 &position );
	glm::vec3 const &Position( void ) const;
	
	void Orientation( const glm::quat &orientation );
	const glm::quat &Orientation( void ) const;

	void Direction( const glm::vec3 &direction );
	glm::vec3 const Direction( void ) const;

	const glm::mat4 ViewMatrix( void ) const;

private:
	glm::vec3	m_position		{ 0.0f, 0.0f, 0.0f };
	glm::quat	m_orientation	{ 1.0f, 0.0f, 0.0f, 0.0f };
};

#endif // TRANSFORMCOMPONENT_HPP
