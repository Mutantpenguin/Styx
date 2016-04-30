#include "CInstanceUniform.hpp"

CInstanceUniform::CInstanceUniform( const GLuint uniformLocation ) :
	m_uniformLocation { uniformLocation }
{
}

CInstanceUniformUINT::CInstanceUniformUINT( const GLuint uniformLocation, const glm::uint value ) :
	CInstanceUniform( uniformLocation ),
	m_value { value }
{
};

void CInstanceUniformUINT::Set( void )
{
	glUniform1ui( m_uniformLocation, m_value );
}
