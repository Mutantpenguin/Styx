#include "CMeshTextureSlot.hpp"

CMeshTextureSlot::CMeshTextureSlot( const std::shared_ptr<const CTexture> &texture, const std::shared_ptr<const CSampler> &sampler ) :
	m_texture { texture },
	m_sampler { sampler }
{
}

void CMeshTextureSlot::BindToUnit( const GLuint unit ) const
{
	m_texture->BindToUnit( unit );
	m_sampler->BindToUnit( unit );
}
