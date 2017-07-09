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
	using TTextures = std::unordered_map< std::string, const std::shared_ptr< CMeshTexture > >;

	CMesh( GLenum Mode, const Primitives::SPrimitive &primitive, const std::shared_ptr< const CMaterial > &mat, const TTextures &textures = TTextures() );

	void SetMaterial( const std::shared_ptr< const CMaterial > &mat );
	const std::shared_ptr< const CMaterial > &Material( void ) const;

	void ChangeTexture( const std::string &name, const std::shared_ptr< const CTexture > &texture, const std::shared_ptr< const CSampler > &sampler );

	const glm::vec3 &BoundingSphereRadiusVector( void ) const;

	const CVAO &VAO( void ) const;

	void BindTextures( void ) const;

private:
	const CVAO	m_vao;

	std::shared_ptr< const CMaterial > m_material;

	const TTextures m_textures;

	std::vector< std::pair< GLuint, const std::shared_ptr< const CMeshTexture > > > m_materialTextureMapping;

	void SetupMaterialTextureMapping( void );

	[[nodiscard]] static glm::vec3 CalculateBoundingSphereRadiusVector( const Primitives::SPrimitive &primitive );

	const glm::vec3	m_boundingSphereRadiusVector;
};

#endif // CMESH_HPP
