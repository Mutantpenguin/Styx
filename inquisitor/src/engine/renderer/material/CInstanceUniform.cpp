#include "CInstanceUniform.hpp"

#include <glm/gtc/type_ptr.hpp>

CInstanceUniformUINT::CInstanceUniformUINT( const glm::uint value ) :
	m_value { value }
{
};

void CInstanceUniformUINT::Set( const GLuint location )
{
	glUniform1ui( location, m_value );
}

CInstanceUniformFLOATVEC4::CInstanceUniformFLOATVEC4( const glm::vec4 &values ) :
	m_values { values }
{
};

void CInstanceUniformFLOATVEC4::Set( const GLuint location )
{
	glUniform4fv( location, 1, glm::value_ptr( m_values ) );
}
