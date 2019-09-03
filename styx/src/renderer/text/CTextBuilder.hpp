#pragma once

#include <memory>

#include "src/renderer/model/CMesh.hpp"
#include "src/renderer/font/CFont.hpp"

class CTextMeshBuilder final
{
public:
	const std::shared_ptr<CMesh> Create( const std::string &str, const std::shared_ptr<CFont> &font ) const;
};
