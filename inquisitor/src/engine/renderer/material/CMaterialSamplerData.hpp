#ifndef CMATERIALSAMPLERDATA_HPP
#define CMATERIALSAMPLERDATA_HPP

#include "src/engine/renderer/texture/CTexture.hpp"
#include "src/engine/renderer/sampler/CSampler.hpp"

class CMaterialSamplerData
{
public:
	CMaterialSamplerData( const std::string &name, const std::shared_ptr< const CTexture > texture, const std::shared_ptr< const CSampler > sampler );

	void BindToUnit( const GLuint unit ) const;

	const std::string &Name( void ) const;

private:
	const std::string m_name;

	const std::shared_ptr< const CTexture > m_texture;
	const std::shared_ptr< const CSampler > m_sampler;
};

#endif // CMATERIALSAMPLERDATA_HPP
