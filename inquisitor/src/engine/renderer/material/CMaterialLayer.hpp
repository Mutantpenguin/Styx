#ifndef CMATERIALLAYER_HPP
#define CMATERIALLAYER_HPP

#include <unordered_map>
#include <memory>

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

	/* TODO shaders
	float	m_animFreq			{ 1.0f };	// interval between animation-stages
	size_t	m_current_texture	{ 1 };		// actual texture to display
	float	m_animtime			{ 0.0f };	// time from engine-start when we should change to next texture in animation-sequenze
	 * */

	std::shared_ptr< CShaderProgram >	m_shader;

	std::unordered_map< GLuint, std::pair< std::shared_ptr< CTexture >, std::shared_ptr< CSampler > > > m_textures;
};

#endif // CMATERIALLAYER_HPP
