#pragma once

#include "src/renderer/text/CText.hpp"
#include "src/renderer/font/CFont.hpp"

class CTextBuilder final
{
public:
	const CText Create( const std::string &str, const std::shared_ptr<CFont> &font ) const;
};
