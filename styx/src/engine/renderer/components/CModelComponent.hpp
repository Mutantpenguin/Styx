#pragma once

#include "src/engine/scene/components/CBaseComponent.hpp"

#include "src/engine/renderer/model/CMesh.hpp"

// TODO this implies it holds a model, but for the moment just holds a mesh, since we don't have models yet
class CModelComponent final : public CBaseComponent
{
private:
	CModelComponent(const CModelComponent& rhs);
	CModelComponent& operator=(const CModelComponent& rhs);

public:
	CModelComponent( const std::shared_ptr< CEntity > &parent, const std::shared_ptr< const CMesh > &mesh );
	~CModelComponent() {};

	static const u16 Index = static_cast<u16>( EComponentIndex::MODEL );

	void Mesh( const std::shared_ptr< const CMesh > &mesh );
	const std::shared_ptr< const CMesh > Mesh( void ) const;

private:
	std::shared_ptr< const CMesh > m_mesh;
};
