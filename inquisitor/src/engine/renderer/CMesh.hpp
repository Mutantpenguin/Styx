#ifndef CMESH_HPP
#define CMESH_HPP

#include <vector>

#include <glm/glm.hpp>

#include "material/CMaterial.hpp"
#include "CVAO.hpp"

class CMesh final
{
public:
	CMesh( GLenum Mode, const Primitives::SPrimitive &primitive, const std::shared_ptr< const CMaterial > &mat, const glm::vec3 &position, const glm::vec3 &orientation, const glm::vec3 &scale );
	CMesh( GLenum Mode, const Primitives::SPrimitive &primitive, const std::shared_ptr< const CMaterial > &mat, const glm::vec3 &position, const glm::vec3 &orientation );
	CMesh( GLenum Mode, const Primitives::SPrimitive &primitive, const std::shared_ptr< const CMaterial > &mat, const glm::vec3 &position );
	CMesh( GLenum Mode, const Primitives::SPrimitive &primitive, const std::shared_ptr< const CMaterial > &mat );

	void SetMaterial( const std::shared_ptr< const CMaterial > &mat );
	const std::shared_ptr< const CMaterial > Material( void ) const;

	void SetScale( const glm::vec3 &position );
	const glm::vec3 &Scale( void ) const;

	void SetPosition( const glm::vec3 &position );
	const glm::vec3 &Position( void ) const;

	void SetOrientation( const glm::vec3 &orientation );
	const glm::vec3 &Orientation( void ) const;

	float BoundingSphereRadius( void ) const;

	const glm::mat4 &ModelMatrix( void ) const;

	const CVAO &VAO( void ) const;

private:
	const CVAO	m_vao;

	void CalculateModelMatrix( void );

	static glm::vec3 CalculatedBoundingSphereRadiusVector( const Primitives::SPrimitive &primitive );
	static float CalculatedBoundingSphereRadius( const glm::vec3 &radiusVector, const glm::vec3 &scale );

	std::shared_ptr< const CMaterial > m_material;

	// TODO put these in the entity, maybe material too
	glm::mat4	m_modelMatrix;

	glm::vec3	m_position		{ 0.0f, 0.0f, 0.0f };
	glm::vec3	m_orientation	{ 0.0f, 0.0f, 0.0f };
	glm::vec3	m_scale			{ 1.0f, 1.0f, 1.0f };

	glm::vec3	m_boundingSphereRadiusVector;
	float		m_boundingSphereRadius;
};

#endif // CMESH_HPP
