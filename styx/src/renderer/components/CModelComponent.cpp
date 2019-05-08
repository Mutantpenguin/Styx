#include "CModelComponent.hpp"

CModelComponent::CModelComponent( const std::shared_ptr<CEntity> &parent, const std::shared_ptr<const CMesh> &mesh ) :
	CBaseComponent( parent ),
	m_mesh { mesh }
{
}

void CModelComponent::Mesh( const std::shared_ptr<const CMesh> &mesh )
{
	m_mesh = mesh;
}

const std::shared_ptr<const CMesh> CModelComponent::Mesh() const
{
	return( m_mesh );
}
