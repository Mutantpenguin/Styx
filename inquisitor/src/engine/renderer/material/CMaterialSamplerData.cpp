#include "src/engine/renderer/material/CMaterialSamplerData.hpp"

CMaterialSamplerData::CMaterialSamplerData( const std::string &name, const std::shared_ptr< const CTexture > &texture, const std::shared_ptr< const CSampler > &sampler ) :
	m_name { name },
	m_texture { texture },
	m_sampler { sampler }
{};

void CMaterialSamplerData::BindToUnit( const GLuint unit ) const
{
	m_texture->BindToUnit( unit );
	m_sampler->BindToUnit( unit );
}

const std::string &CMaterialSamplerData::Name( void ) const
{
	return( m_name );
}
