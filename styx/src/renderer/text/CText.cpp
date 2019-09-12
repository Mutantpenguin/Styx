#include "CText.hpp"

#include "CTextGeometryBuilder.hpp"

CText::CText( const std::shared_ptr<const CFont> &font, const STextOptions &textOptions, const std::string &str, const std::shared_ptr<CMesh> &mesh ) :
	m_font { font },
	m_str { str },
	m_textOptions { textOptions },
	m_mesh { mesh }
{}

void CText::Text( const std::string &str )
{
	m_str = str;

	RecreateMesh();
}

std::string &CText::Text()
{
	return( m_str );
}

void CText::TextOptions( const STextOptions &textOptions )
{
	m_textOptions = textOptions;

	RecreateMesh();
}

STextOptions &CText::TextOptions()
{
	return( m_textOptions );
}

void CText::Font( const std::shared_ptr<const CFont> &font )
{
	m_font = font;

	RecreateMesh();
}

std::shared_ptr<const CFont> &CText::Font()
{
	return( m_font );
}

const std::shared_ptr<CMesh> &CText::Mesh() const
{
	return( m_mesh );
}

void CText::RecreateMesh()
{
	m_mesh->SetGeometry( CTextGeometryBuilder::Build( m_font, m_textOptions, m_str ) );
}