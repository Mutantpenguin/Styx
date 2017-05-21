#ifndef CMESH_HPP
#define CMESH_HPP

#include <vector>

#include <glm/glm.hpp>

#include "src/engine/renderer/model/CMeshTexture.hpp"

#include "src/engine/renderer/material/CMaterial.hpp"
#include "src/engine/renderer/CVAO.hpp"

class CMesh final
{
friend class CModelLoader;

public:
	using TTextures = std::unordered_map< std::string, std::shared_ptr< CMeshTexture > >;

	CMesh( GLenum Mode, const Primitives::SPrimitive &primitive, const std::shared_ptr< const CMaterial > &mat, const glm::vec3 &position, const glm::vec3 &orientation, const glm::vec3 &scale, const TTextures &textures = TTextures() );
	CMesh( GLenum Mode, const Primitives::SPrimitive &primitive, const std::shared_ptr< const CMaterial > &mat, const glm::vec3 &position, const glm::vec3 &orientation, const TTextures &textures = TTextures() );
	CMesh( GLenum Mode, const Primitives::SPrimitive &primitive, const std::shared_ptr< const CMaterial > &mat, const glm::vec3 &position, const TTextures &textures = TTextures() );
	CMesh( GLenum Mode, const Primitives::SPrimitive &primitive, const std::shared_ptr< const CMaterial > &mat, const TTextures &textures = TTextures());

	void SetMaterial( const std::shared_ptr< const CMaterial > &mat );
	const std::shared_ptr< const CMaterial > &Material( void ) const;

	void ChangeTexture( const std::string &name, const std::shared_ptr< const CTexture > &texture, const std::shared_ptr< const CSampler > &sampler );

	void SetScale( const glm::vec3 &position );
	const glm::vec3 &Scale( void ) const;

	void SetPosition( const glm::vec3 &position );
	const glm::vec3 &Position( void ) const;

	void SetOrientation( const glm::vec3 &orientation );
	const glm::vec3 &Orientation( void ) const;

	float BoundingSphereRadius( void ) const;

	const glm::mat4 &ModelMatrix( void ) const;

	const CVAO &VAO( void ) const;

	void BindTextures( void ) const;

private:
	const CVAO	m_vao;

	std::shared_ptr< const CMaterial > m_material;

	const TTextures m_textures;

	std::vector< std::pair< GLuint, const std::shared_ptr< const CMeshTexture > > > m_materialTextureMapping;

	void SetupMaterialTextureMapping( void );

	void CalculateModelMatrix( void );

	static glm::vec3 CalculatedBoundingSphereRadiusVector( const Primitives::SPrimitive &primitive );
	static float CalculatedBoundingSphereRadius( const glm::vec3 &radiusVector, const glm::vec3 &scale );

	// TODO put these in the entity, maybe material too
	glm::mat4	m_modelMatrix;

	glm::vec3	m_position		{ 0.0f, 0.0f, 0.0f };
	glm::vec3	m_orientation	{ 0.0f, 0.0f, 0.0f };
	glm::vec3	m_scale			{ 1.0f, 1.0f, 1.0f };

	glm::vec3	m_boundingSphereRadiusVector;
	float		m_boundingSphereRadius;
};

#endif // CMESH_HPP
