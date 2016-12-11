#include "CMaterialUniform.hpp"

#include <glm/gtc/type_ptr.hpp>

CMaterialUniformUINT::CMaterialUniformUINT( const glm::uint value ) :
	m_value { value }
{
};

void CMaterialUniformUINT::Set( const GLuint location ) const
{
	glUniform1ui( location, m_value );
}

CMaterialUniformFLOATVEC4::CMaterialUniformFLOATVEC4( const glm::vec4 &values ) :
	m_values { values }
{
};

void CMaterialUniformFLOATVEC4::Set( const GLuint location ) const
{
	glUniform4fv( location, 1, glm::value_ptr( m_values ) );
}
