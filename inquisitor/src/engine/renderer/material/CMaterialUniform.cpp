#include "CMaterialUniform.hpp"

#include <glm/gtc/type_ptr.hpp>

CMaterialUniform::CMaterialUniform( const std::string &name ) :
	m_name { name }
{}

const std::string &CMaterialUniform::Name( void ) const
{
	return( m_name );
}

CMaterialUniformFLOAT::CMaterialUniformFLOAT( const std::string &name, const glm::float32 value ) :
	CMaterialUniform( name ),
	m_value { value }
{
};

void CMaterialUniformFLOAT::Set( const GLuint location ) const
{
	glUniform1f( location, m_value );
}


CMaterialUniformUINT::CMaterialUniformUINT( const std::string &name, const glm::uint value ) :
	CMaterialUniform( name ),
	m_value { value }
{
};

void CMaterialUniformUINT::Set( const GLuint location ) const
{
	glUniform1ui( location, m_value );
}


CMaterialUniformFLOATVEC4::CMaterialUniformFLOATVEC4( const std::string &name, const glm::vec4 &values ) :
	CMaterialUniform( name ),
	m_values { values }
{
};

void CMaterialUniformFLOATVEC4::Set( const GLuint location ) const
{
	glUniform4fv( location, 1, glm::value_ptr( m_values ) );
}
