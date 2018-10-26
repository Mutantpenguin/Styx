#ifndef CSAMPLERMANAGER_HPP
#define CSAMPLERMANAGER_HPP

#include <array>
#include <memory>

#include "src/engine/helper/Types.hpp"

#include "src/engine/renderer/GL.h"

#include "src/engine/system/CSettings.hpp"

#include "CSampler.hpp"

class CSamplerManager final
{
public:
	explicit CSamplerManager( const CSettings &p_settings );
	~CSamplerManager( void );

	[[nodiscard]] bool GetFromString( const std::string &string, std::shared_ptr< const CSampler > &sampler ) const;

	[[nodiscard]] const std::shared_ptr< const CSampler > GetFromType( const CSampler::SamplerType type ) const;

private:
	u8 m_iAnisotropicLevel;

	[[nodiscard]] const std::shared_ptr< const CSampler > Generate( const CSampler::SamplerType type );

	std::array< std::shared_ptr< const CSampler >, static_cast< u8 >( CSampler::SamplerType::MAX ) > m_samplers;
};

#endif // CSAMPLERMANAGER_HPP
