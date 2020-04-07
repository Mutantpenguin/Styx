#pragma once

#include "src/scene/components/CBaseComponent.hpp"

#include "src/renderer/model/CMesh.hpp"

// TODO this implies it holds a model, but for the moment just holds a mesh, since we don't have models yet
class CGuiModelComponent final : public CBaseComponent
{
private:
	CGuiModelComponent( const CGuiModelComponent& rhs );
	CGuiModelComponent& operator=( const CGuiModelComponent& rhs );

public:
	CGuiModelComponent( const std::shared_ptr<CEntity> &parent, const std::shared_ptr<const CMesh> &mesh );
	~CGuiModelComponent() {};

	static const u16 Index = static_cast<u16>( EComponentIndex::GUIMODEL );

	std::shared_ptr<const CMesh> Mesh;
};
