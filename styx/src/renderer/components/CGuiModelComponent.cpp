#include "CGuiModelComponent.hpp"

CGuiModelComponent::CGuiModelComponent( const std::shared_ptr<CEntity> &parent, const std::shared_ptr<const CMesh> &mesh ) :
	CBaseComponent( parent ),
	Mesh{ mesh }
{}