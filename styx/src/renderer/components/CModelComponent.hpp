#pragma once

#include "src/scene/components/CBaseComponent.hpp"

#include "src/renderer/model/CMesh.hpp"

// TODO this implies it holds a model, but for the moment just holds a mesh, since we don't have models yet
class CModelComponent final : public CBaseComponent
{
private:
	CModelComponent(const CModelComponent& rhs);
	CModelComponent& operator=(const CModelComponent& rhs);

public:
	CModelComponent( const std::shared_ptr<CEntity> &parent, const std::shared_ptr<const CMesh> &mesh );
	~CModelComponent() {};

	static const u16 Index = static_cast<u16>( EComponentIndex::MODEL );

	std::shared_ptr<const CMesh> Mesh;
};
