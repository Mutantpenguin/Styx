#ifndef CMATERIALLAYER_HPP
#define CMATERIALLAYER_HPP

#include <unordered_map>
#include <memory>

#include "CInstanceUniform.hpp"
#include "../shader/CShaderProgram.hpp"
#include "../texture/CTexture.hpp"
#include "../sampler/CSampler.hpp"
#include "CTexCoordMods.hpp"

class CMaterialManager;

class CMaterialLayer final
{
	friend class CRenderer;
	friend class CMaterialManager;
	friend class CMaterialLoader;
	friend class CMaterial;

public:
	CMaterialLayer( void ) {};

	void Update( const float delta );

private:
	glm::mat3	m_textureMatrix;

	std::vector< std::shared_ptr< CTexCoordMod > > m_texcoordmods;

	std::shared_ptr< CShaderProgram >	m_shader;

	std::unordered_map< GLuint, std::pair< std::shared_ptr< CTexture >, std::shared_ptr< CSampler > > > m_textures;

	std::unordered_map< GLuint, std::unique_ptr< CInstanceUniform > > m_instanceUniforms;
};

#endif // CMATERIALLAYER_HPP
