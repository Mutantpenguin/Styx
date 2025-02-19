#pragma once

#include <vector>
#include <unordered_map>

#include <glm/glm.hpp>

#include "src/renderer/model/CMeshTextureSlot.hpp"

#include "src/renderer/material/CMaterial.hpp"
#include "src/renderer/CVertexArrayObject.hpp"

class CMesh final
{
friend class CModelLoader;

public:
	using TMeshTextureSlots = std::unordered_map<std::string, const std::shared_ptr<CMeshTextureSlot>>;

	template<typename T>
	CMesh( const Geometry<T> &geometry, const std::shared_ptr<const CMaterial> &mat, const TMeshTextureSlots &textureSlots = TMeshTextureSlots(), const bool dynamic = false ) :
		m_vao( geometry, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW ),
		m_material { mat },
		m_textureSlots { textureSlots },
		BoundingSphereRadiusVector { geometry.CalculateBoundingSphereRadiusVector() }
	{
		SetupMaterialTextureSlotMapping();
	}

	template<typename T>
	void SetGeometry( const Geometry<T> &geometry )
	{
		m_vao.Rebuild( geometry );
		BoundingSphereRadiusVector = geometry.CalculateBoundingSphereRadiusVector();
	}

	void SetMaterial( const std::shared_ptr<const CMaterial> &mat );
	const std::shared_ptr<const CMaterial> &Material() const;

	void ChangeTexture( const std::string &slotName, const std::shared_ptr<const CTexture> &texture );
	void ChangeSampler( const std::string &slotName, const std::shared_ptr<const CSampler> &sampler );
	void ChangeTextureAndSampler( const std::string &slotName, const std::shared_ptr<const CTexture> &texture, const std::shared_ptr<const CSampler> &sampler );

	void Bind() const;

	void Draw() const;

private:
	CVertexArrayObject m_vao;

	std::shared_ptr<const CMaterial> m_material;

	const TMeshTextureSlots m_textureSlots;

	std::vector<std::pair<GLuint, const std::shared_ptr<const CMeshTextureSlot>>> m_materialTextureSlotMapping;

	void SetupMaterialTextureSlotMapping();

public:
	glm::vec3	BoundingSphereRadiusVector;
};
