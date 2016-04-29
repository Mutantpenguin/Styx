#ifndef CSAMPLERMANAGER_HPP
#define CSAMPLERMANAGER_HPP

#include <array>
#include <memory>

#include "../GL.h"

#include "../../system/CSettings.hpp"

#include "CSampler.hpp"

class CSamplerManager final
{
friend class CRenderer;

public:
	bool SamplerFromString( const std::string &string, std::shared_ptr< CSampler > &sampler ) const;

	std::shared_ptr< CSampler > SamplerFromType( CSampler::Type type ) const;

private:
	CSamplerManager( const CSettings &p_settings );

	bool Init( void );

	unsigned int m_iAnisotropicLevel;

	std::shared_ptr< CSampler > Generate( CSampler::Type type );

	std::array< std::shared_ptr< CSampler >, static_cast< std::uint8_t >( CSampler::Type::MAX ) > m_samplers;
};

#endif // CSAMPLERMANAGER_HPP
