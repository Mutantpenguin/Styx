#include "CSamplerManager.hpp"

#include "src/logger/CLogger.hpp"

#include "src/core/StyxException.hpp"

CSamplerManager::CSamplerManager( const COpenGlAdapter &openGlAdapter ) :
	m_samplers()
{
	const auto sampler2DRepeat = Generate( CSampler::SamplerType::REPEAT_2D );
	sampler2DRepeat->Parametere( GL_TEXTURE_WRAP_S, GL_REPEAT );
	sampler2DRepeat->Parametere( GL_TEXTURE_WRAP_T, GL_REPEAT );
	sampler2DRepeat->Parametere( GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	sampler2DRepeat->Parametere( GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	const auto sampler2DBorder = Generate( CSampler::SamplerType::BORDER_2D );
	sampler2DBorder->Parametere( GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
	sampler2DBorder->Parametere( GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
	sampler2DBorder->Parametere( GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	sampler2DBorder->Parametere( GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	const auto sampler2DEdge = Generate( CSampler::SamplerType::EDGE_2D );
	sampler2DEdge->Parametere( GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	sampler2DEdge->Parametere( GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	sampler2DEdge->Parametere( GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	sampler2DEdge->Parametere( GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	const auto sampler2DRepeatBorder = Generate( CSampler::SamplerType::REPEAT_BORDER_2D );
	sampler2DRepeatBorder->Parametere( GL_TEXTURE_WRAP_S, GL_REPEAT );
	sampler2DRepeatBorder->Parametere( GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
	sampler2DRepeatBorder->Parametere( GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	sampler2DRepeatBorder->Parametere( GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	auto anisotropicLevel = openGlAdapter.AnisotropicLevel();
	if( anisotropicLevel > 1 )
	{
		sampler2DRepeat->Parameteri( GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropicLevel );
		sampler2DBorder->Parameteri( GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropicLevel );
		sampler2DEdge->Parameteri( GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropicLevel );
		sampler2DRepeatBorder->Parameteri( GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropicLevel );
	}

	const auto samplerCubeRepeat = Generate( CSampler::SamplerType::REPEAT_CUBE );
	samplerCubeRepeat->Parametere( GL_TEXTURE_WRAP_S, GL_REPEAT );
	samplerCubeRepeat->Parametere( GL_TEXTURE_WRAP_T, GL_REPEAT );
	samplerCubeRepeat->Parametere( GL_TEXTURE_WRAP_R, GL_REPEAT );
	samplerCubeRepeat->Parametere( GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	samplerCubeRepeat->Parametere( GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	const auto samplerCubeBorder = Generate( CSampler::SamplerType::BORDER_CUBE );
	samplerCubeBorder->Parametere( GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
	samplerCubeBorder->Parametere( GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
	samplerCubeBorder->Parametere( GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER );
	samplerCubeBorder->Parametere( GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	samplerCubeBorder->Parametere( GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	const auto samplerCubeEdge = Generate( CSampler::SamplerType::EDGE_CUBE );
	samplerCubeEdge->Parametere( GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	samplerCubeEdge->Parametere( GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	samplerCubeEdge->Parametere( GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
	samplerCubeEdge->Parametere( GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	samplerCubeEdge->Parametere( GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	logINFO( "sampler manager was initialized" );
}

CSamplerManager::~CSamplerManager()
{
	logINFO( "sampler manager is shutting down" );
}

bool CSamplerManager::GetFromString( const std::string &string, std::shared_ptr<const CSampler> &sampler ) const
{
	if( string == "REPEAT_2D" )
	{
		sampler = m_samplers[ static_cast<u8>( CSampler::SamplerType::REPEAT_2D ) ];
	}
	else if( string == "BORDER_2D" )
	{
		sampler = m_samplers[ static_cast<u8>( CSampler::SamplerType::BORDER_2D ) ];
	}
	else if( string == "EDGE_2D" )
	{
		sampler = m_samplers[ static_cast<u8>( CSampler::SamplerType::EDGE_2D ) ];
	}
	else if( string == "REPEAT_BORDER_2D" )
	{
		sampler = m_samplers[ static_cast<u8>( CSampler::SamplerType::REPEAT_BORDER_2D ) ];
	}
	else if( string == "REPEAT_CUBE" )
	{
		sampler = m_samplers[ static_cast<u8>( CSampler::SamplerType::REPEAT_CUBE ) ];
	}
	else if( string == "BORDER_CUBE" )
	{
		sampler = m_samplers[ static_cast<u8>( CSampler::SamplerType::BORDER_CUBE ) ];
	}
	else if( string == "EDGE_CUBE" )
	{
		sampler = m_samplers[ static_cast<u8>( CSampler::SamplerType::EDGE_CUBE ) ];
	}
	else
	{
		logWARNING( "unknown sampler type '{0}'", string );
		sampler = nullptr;
		return( false );
	}

	return( true );
}

const std::shared_ptr<const CSampler> CSamplerManager::GetFromType( const CSampler::SamplerType type ) const
{
	return( m_samplers[ static_cast<u8>( type ) ] );
}

const std::shared_ptr<CSampler> CSamplerManager::Generate( CSampler::SamplerType type )
{
	const u8 index = static_cast<u8>( type );

	if( 0 != m_samplers[ index ] )
	{
		THROW_STYX_EXCEPTION( "sampler with index {0} already set", index )
	}

	auto sampler = std::make_shared<CSampler>();

	m_samplers[ index ] = sampler;

	return( sampler );
}
