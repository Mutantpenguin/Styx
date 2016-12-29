#include "CSamplerManager.hpp"

#include "src/engine/logger/CLogger.hpp"

CSamplerManager::CSamplerManager( const CSettings &p_settings ) :
	m_iAnisotropicLevel { p_settings.renderer.textures.anisotropic },
	m_samplers()
{
	if( m_iAnisotropicLevel > 1 )
	{
		GLfloat fMaxSupportedAnisotropy;
		glGetFloatv( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fMaxSupportedAnisotropy );

		if( m_iAnisotropicLevel > fMaxSupportedAnisotropy )
		{
			logWARNING( "anisotropic level of '{0}' is higher than the highest supported level of '{1}' which will now be used instead", m_iAnisotropicLevel, fMaxSupportedAnisotropy );
			m_iAnisotropicLevel = fMaxSupportedAnisotropy;
		}
		else
		{
			logINFO( "anisotropic filtering with a level of '{0}' will be used", m_iAnisotropicLevel );
		}
	}
	else
	{
		logINFO( "anisotropic filtering is disbabled" );
	}

	const auto sampler2DRepeat = Generate( CSampler::Type::REPEAT_2D );
	sampler2DRepeat->Parametere( GL_TEXTURE_WRAP_S, GL_REPEAT );
	sampler2DRepeat->Parametere( GL_TEXTURE_WRAP_T, GL_REPEAT );
	sampler2DRepeat->Parametere( GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	sampler2DRepeat->Parametere( GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	const auto sampler2DBorder = Generate( CSampler::Type::BORDER_2D );
	sampler2DBorder->Parametere( GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
	sampler2DBorder->Parametere( GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
	sampler2DBorder->Parametere( GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	sampler2DBorder->Parametere( GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	const auto sampler2DEdge = Generate( CSampler::Type::EDGE_2D );
	sampler2DEdge->Parametere( GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	sampler2DEdge->Parametere( GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	sampler2DEdge->Parametere( GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	sampler2DEdge->Parametere( GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	const auto sampler2DRepeatBorder = Generate( CSampler::Type::REPEAT_BORDER_2D );
	sampler2DRepeatBorder->Parametere( GL_TEXTURE_WRAP_S, GL_REPEAT );
	sampler2DRepeatBorder->Parametere( GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
	sampler2DRepeatBorder->Parametere( GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	sampler2DRepeatBorder->Parametere( GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	if( m_iAnisotropicLevel > 1 )
	{
		sampler2DRepeat->Parameteri( GL_TEXTURE_MAX_ANISOTROPY_EXT, m_iAnisotropicLevel );
		sampler2DBorder->Parameteri( GL_TEXTURE_MAX_ANISOTROPY_EXT, m_iAnisotropicLevel );
		sampler2DEdge->Parameteri( GL_TEXTURE_MAX_ANISOTROPY_EXT, m_iAnisotropicLevel );
		sampler2DRepeatBorder->Parameteri( GL_TEXTURE_MAX_ANISOTROPY_EXT, m_iAnisotropicLevel );
	}

	const auto samplerCubeRepeat = Generate( CSampler::Type::REPEAT_CUBE );
	samplerCubeRepeat->Parametere( GL_TEXTURE_WRAP_S, GL_REPEAT );
	samplerCubeRepeat->Parametere( GL_TEXTURE_WRAP_T, GL_REPEAT );
	samplerCubeRepeat->Parametere( GL_TEXTURE_WRAP_R, GL_REPEAT );
	samplerCubeRepeat->Parametere( GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	samplerCubeRepeat->Parametere( GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	const auto samplerCubeBorder = Generate( CSampler::Type::BORDER_CUBE );
	samplerCubeBorder->Parametere( GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
	samplerCubeBorder->Parametere( GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
	samplerCubeBorder->Parametere( GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER );
	samplerCubeBorder->Parametere( GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	samplerCubeBorder->Parametere( GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	const auto samplerCubeEdge = Generate( CSampler::Type::EDGE_CUBE );
	samplerCubeEdge->Parametere( GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	samplerCubeEdge->Parametere( GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	samplerCubeEdge->Parametere( GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
	samplerCubeEdge->Parametere( GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	samplerCubeEdge->Parametere( GL_TEXTURE_MAG_FILTER, GL_LINEAR );
}

bool CSamplerManager::SamplerFromString( const std::string &string, std::shared_ptr< const CSampler > &sampler ) const
{
	if( string == "REPEAT_2D" )
	{
		sampler = m_samplers[ static_cast< std::uint8_t >( CSampler::Type::REPEAT_2D ) ];
	}
	else if( string == "BORDER_2D" )
	{
		sampler = m_samplers[ static_cast< std::uint8_t >( CSampler::Type::BORDER_2D ) ];
	}
	else if( string == "EDGE_2D" )
	{
		sampler = m_samplers[ static_cast< std::uint8_t >( CSampler::Type::EDGE_2D ) ];
	}
	else if( string == "REPEAT_BORDER_2D" )
	{
		sampler = m_samplers[ static_cast< std::uint8_t >( CSampler::Type::REPEAT_BORDER_2D ) ];
	}
	else if( string == "REPEAT_CUBE" )
	{
		sampler = m_samplers[ static_cast< std::uint8_t >( CSampler::Type::REPEAT_CUBE ) ];
	}
	else if( string == "BORDER_CUBE" )
	{
		sampler = m_samplers[ static_cast< std::uint8_t >( CSampler::Type::BORDER_CUBE ) ];
	}
	else if( string == "EDGE_CUBE" )
	{
		sampler = m_samplers[ static_cast< std::uint8_t >( CSampler::Type::EDGE_CUBE ) ];
	}
	else
	{
		logWARNING( "unknown sampler type '{0}'", string );
		return( false );
	}

	return( true );
}

std::shared_ptr< const CSampler > CSamplerManager::SamplerFromType( CSampler::Type type ) const
{
	return( m_samplers[ static_cast< std::uint8_t >( type ) ] );
}

std::shared_ptr< const CSampler > CSamplerManager::Generate( CSampler::Type type )
{
	const std::uint8_t index = static_cast< std::uint8_t >( type );

	if( 0 != m_samplers[ index ] )
	{
		logERROR( "sampler with index {0} already set", index );
		throw std::exception();
	}

	auto sampler = std::make_shared< CSampler >();

	m_samplers[ index ] = sampler;

	return( sampler );
}
