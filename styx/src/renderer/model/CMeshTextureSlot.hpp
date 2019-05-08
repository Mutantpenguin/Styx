#pragma once

#include <memory>

#include "src/renderer/texture/CTexture.hpp"
#include "src/renderer/sampler/CSampler.hpp"

class CMeshTextureSlot final
{
public:
	CMeshTextureSlot( const std::shared_ptr<const CTexture> &texture, const std::shared_ptr<const CSampler> &sampler );

	void BindToUnit( const GLuint unit ) const;

	std::shared_ptr<const CTexture>	m_texture;
	std::shared_ptr<const CSampler>	m_sampler;
};
