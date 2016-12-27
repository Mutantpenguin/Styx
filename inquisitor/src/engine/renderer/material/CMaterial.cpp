#include "CMaterial.hpp"

#include "src/engine/renderer/CGLState.hpp"

CMaterial::CMaterial( const std::string &name ) :
	m_name { name }
{
}

CMaterial::~CMaterial( void )
{
}

void CMaterial::Setup( void ) const
{
	CGLState::CullFace( m_bCullFace, m_cullfacemode );
	CGLState::PolygonMode( m_polygonmode );
	CGLState::Blending( m_blending, m_blendSrc, m_blendDst );
}

bool CMaterial::Blending( void ) const
{
	return( m_blending );
};

const std::shared_ptr< const CShaderProgram > CMaterial::Shader( void ) const
{
	return( m_shader );
}

const std::unordered_map< GLuint, std::unique_ptr< const CMaterialSamplerData > > &CMaterial::SamplerData( void ) const
{
	return( m_samplerData );
}

const std::unordered_map< GLuint, std::unique_ptr< const CMaterialUniform > > &CMaterial::MaterialUniforms( void ) const
{
	return( m_materialUniforms );
}

const std::string &CMaterial::Name( void ) const
{
	return( m_name );
}
