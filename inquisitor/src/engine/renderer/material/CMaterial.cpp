#include "CMaterial.hpp"

CMaterial::CMaterial( const std::string &name ) :
	m_name { name }
{
}

CMaterial::~CMaterial( void )
{
	m_layers.clear();
}

void CMaterial::Update( const float delta )
{
	for( const std::shared_ptr< CMaterialLayer > &layer : m_layers )
    {
        layer->Update( delta );
    }
}

const std::vector< std::shared_ptr< CMaterialLayer > > &CMaterial::Layers( void ) const
{
	return( m_layers );
}

std::shared_ptr< CMaterialLayer > CMaterial::CreateLayer( void )
{
	m_layers.emplace_back( std::make_shared< CMaterialLayer >() );

	return( m_layers.back() );
}
