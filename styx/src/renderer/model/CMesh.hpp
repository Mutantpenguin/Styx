#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "src/renderer/model/CMeshTextureSlot.hpp"

#include "src/renderer/material/CMaterial.hpp"
#include "src/renderer/CVAO.hpp"

class CMesh final
{
friend class CModelLoader;

public:
	using TMeshTextureSlots = std::unordered_map< std::string, const std::shared_ptr< CMeshTextureSlot > >;

	CMesh( GLenum Mode, const Primitives::SPrimitive &primitive, const std::shared_ptr< const CMaterial > &mat, const TMeshTextureSlots &textureSlots = TMeshTextureSlots() );

	void SetMaterial( const std::shared_ptr< const CMaterial > &mat );
	const std::shared_ptr< const CMaterial > &Material() const;

	void ChangeTexture( const std::string &slotName, const std::shared_ptr< const CTexture > &texture );
	void ChangeSampler( const std::string &slotName, const std::shared_ptr< const CSampler > &sampler );
	void ChangeTextureAndSampler( const std::string &slotName, const std::shared_ptr< const CTexture > &texture, const std::shared_ptr< const CSampler > &sampler );

	const glm::vec3 &BoundingSphereRadiusVector() const;

	const CVAO &VAO() const;

	void BindTextures() const;

private:
	const CVAO	m_vao;

	std::shared_ptr< const CMaterial > m_material;

	const TMeshTextureSlots m_textureSlots;

	std::vector< std::pair< GLuint, const std::shared_ptr< const CMeshTextureSlot > > > m_materialTextureSlotMapping;

	void SetupMaterialTextureSlotMapping();

	[[nodiscard]] static glm::vec3 CalculateBoundingSphereRadiusVector( const Primitives::SPrimitive &primitive );

	const glm::vec3	m_boundingSphereRadiusVector;
};
