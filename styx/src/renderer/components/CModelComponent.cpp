#include "CModelComponent.hpp"

CModelComponent::CModelComponent( const std::shared_ptr<CEntity> &parent, const std::shared_ptr<const CMesh> &mesh ) :
	CBaseComponent( parent ),
	Mesh { mesh }
{}