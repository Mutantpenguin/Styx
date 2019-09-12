#pragma once

#include <memory>
#include <string>

#include "external/fmt/format.h"

#include "STextOptions.hpp"

#include "src/renderer/font/CFont.hpp"
#include "src/renderer/model/CMesh.hpp"

class CText final
{
public:
	CText( const std::shared_ptr<const CFont> &font, const STextOptions &textOptions, const std::string &str, const std::shared_ptr<CMesh> &mesh );

	template<typename... Args>
	void Text( const std::string &str, const Args &... args )
	{
		Text( fmt::format( str, args... ) );
	}

	void Text( const std::string &str );
	std::string &Text();

	void TextOptions( const STextOptions &textOptions );
	STextOptions &TextOptions();

	void Font( const std::shared_ptr<const CFont> &font );
	std::shared_ptr<const CFont> &Font();

	const std::shared_ptr<CMesh> &Mesh() const;

private:
	std::shared_ptr<const CFont> m_font;

	std::string m_str;

	STextOptions m_textOptions;

	const std::shared_ptr<CMesh> m_mesh;

	void RecreateMesh();
};