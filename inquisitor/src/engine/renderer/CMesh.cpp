#include "CMesh.hpp"

#include <algorithm>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>


CMesh::CMesh( GLenum Mode, const Primitives::SPrimitive &primitive, const std::shared_ptr< CMaterial > &mat, const glm::vec3 &scale, const glm::vec3 &position, const glm::vec3 &orientation ) :
	m_vao( Mode, primitive ),
	m_material { mat },
	m_position { position },
	m_scale { scale },
	m_orientation { orientation },
	m_boundingSphereRadiusVector { CalculatedBoundingSphereRadiusVector( primitive ) },
	m_boundingSphereRadius { CalculatedBoundingSphereRadiusVector( m_boundingSphereRadiusVector, m_scale ) }
{
	CalculateModelMatrix();
}

/**	Sets the material and creates enough texcoord-buffers for the coord-modifications of every layer. */
void CMesh::SetMaterial( const std::shared_ptr< CMaterial > &mat )
{
	m_material = mat;
}

const std::shared_ptr< const CMaterial > CMesh::Material( void ) const
{
	return( m_material );
}

void CMesh::SetScale( const glm::vec3 &scale )
{
	m_scale = scale;
	m_boundingSphereRadius = CalculatedBoundingSphereRadiusVector( m_boundingSphereRadiusVector, m_scale );
	CalculateModelMatrix();
}

const glm::vec3 &CMesh::Scale( void ) const
{
	return( m_scale );
}

void CMesh::SetPosition( const glm::vec3 &position )
{
	m_position = position;
	CalculateModelMatrix();
}

const glm::vec3 &CMesh::Position( void ) const
{
	return( m_position );
}

void CMesh::SetOrientation( const glm::vec3 &orientation )
{
	m_orientation = orientation;
	CalculateModelMatrix();
}

const glm::vec3 &CMesh::Orientation( void ) const
{
	return( m_orientation );
}

const CVAO &CMesh::VAO( void ) const
{
	return( m_vao );
}

float CMesh::BoundingSphereRadius( void ) const
{
	return( m_boundingSphereRadius );
}

const glm::mat4 &CMesh::ModelMatrix( void ) const
{
	return( m_modelMatrix );
}

void CMesh::CalculateModelMatrix( void )
{
	m_modelMatrix = glm::mat4();

	m_modelMatrix = glm::translate( m_modelMatrix, m_position );

	const glm::vec3 rotationRadians = glm::vec3( glm::radians( m_orientation.x ), glm::radians( m_orientation.y ), glm::radians( m_orientation.z ) );
	m_modelMatrix = m_modelMatrix * glm::toMat4( glm::quat( rotationRadians ) );

	m_modelMatrix = glm::scale( m_modelMatrix, m_scale );
}

glm::vec3 CMesh::CalculatedBoundingSphereRadiusVector( const Primitives::SPrimitive &primitive )
{
	return( *std::max_element( primitive.vertices.begin(), primitive.vertices.end(), [&]( glm::vec3 a, glm::vec3 b ){ return( glm::length2( a ) > glm::length2( b ) ); } ) );
}

float CMesh::CalculatedBoundingSphereRadiusVector( const glm::vec3 &radiusVector, const glm::vec3 &scale )
{
	return( glm::length( radiusVector * scale ) );
}
