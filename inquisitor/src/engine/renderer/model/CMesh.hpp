#ifndef CMESH_HPP
#define CMESH_HPP

#include <vector>

#include <glm/glm.hpp>

#include "src/engine/renderer/model/CMeshTextureSlot.hpp"

#include "src/engine/renderer/material/CMaterial.hpp"
#include "src/engine/renderer/CVAO.hpp"

class CMesh final
{
friend class CModelLoader;

public:
	using TMeshTextureSlots = std::unordered_map< std::string, const std::shared_ptr< CMeshTextureSlot > >;

	CMesh( GLenum Mode, const Primitives::SPrimitive &primitive, const std::shared_ptr< const CMaterial > &mat, const TMeshTextureSlots &textureSlots = TMeshTextureSlots() );

	void SetMaterial( const std::shared_ptr< const CMaterial > &mat );
	const std::shared_ptr< const CMaterial > &Material( void ) const;

	void ChangeTexture( const std::string &slotName, const std::shared_ptr< const CTexture > &texture );
	void ChangeSampler( const std::string &slotName, const std::shared_ptr< const CSampler > &sampler );
	void ChangeTextureAndSampler( const std::string &slotName, const std::shared_ptr< const CTexture > &texture, const std::shared_ptr< const CSampler > &sampler );

	const glm::vec3 &BoundingSphereRadiusVector( void ) const;

	const CVAO &VAO( void ) const;

	void BindTextures( void ) const;

private:
	const CVAO	m_vao;

	std::shared_ptr< const CMaterial > m_material;

	const TMeshTextureSlots m_textureSlots;

	std::vector< std::pair< GLuint, const std::shared_ptr< const CMeshTextureSlot > > > m_materialTextureSlotMapping;

	void SetupMaterialTextureMapping( void );

	[[nodiscard]] static glm::vec3 CalculateBoundingSphereRadiusVector( const Primitives::SPrimitive &primitive );

	const glm::vec3	m_boundingSphereRadiusVector;
};

#endif // CMESH_HPP
