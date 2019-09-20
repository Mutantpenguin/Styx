#pragma once

#include <array>
#include <memory>

#include "src/renderer/GL.h"

#include "src/renderer/COpenGlAdapter.hpp"

#include "CSampler.hpp"

class CSamplerManager final
{
public:
	explicit CSamplerManager( const COpenGlAdapter &openGlAdapter );
	~CSamplerManager();

	[[nodiscard]] bool GetFromString( const std::string &string, std::shared_ptr<const CSampler> &sampler ) const;

	[[nodiscard]] const std::shared_ptr<const CSampler> GetFromType( const CSampler::SamplerType type ) const;

private:
	[[nodiscard]] const std::shared_ptr<CSampler> Generate( const CSampler::SamplerType type );

	std::array<std::shared_ptr<const CSampler>, static_cast<u8>( CSampler::SamplerType::MAX )> m_samplers;
};
