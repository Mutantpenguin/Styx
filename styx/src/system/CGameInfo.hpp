#pragma once

#include <string>
#include <vector>
#include <filesystem>

class CGameInfo final
{
public:
	explicit CGameInfo( const std::filesystem::path &gamePath );

	const std::filesystem::path &GetPath() const;

	const std::string &GetName() const;
	const std::string &GetShortName() const;
	const std::string &GetInfo() const;
	const std::string &GetVersion() const;
	const std::string &GetOrganisation() const;
	const std::string &GetAuthor() const;
	const std::string &GetAuthorEmail() const;
	const std::string &GetWebsite() const;

	const std::string &GetIconPath() const;

	const std::vector<std::string> &GetAssets() const;
	const std::vector<std::string> &GetTemplates() const;

private:
	CGameInfo( const CGameInfo &rhs ) = delete;
	CGameInfo& operator = ( const CGameInfo &rhs ) = delete;

	static const std::string gameinfoFilename;

	const std::filesystem::path m_gamePath;

	std::string m_name;
	std::string m_name_short;
	std::string m_info;
	std::string m_version;
	std::string m_organisation;
	std::string m_author;
	std::string m_author_email;
	std::string m_website;

	std::string m_icon;

	std::vector<std::string> m_assets;
	std::vector<std::string> m_templates;

	std::string m_menu_background;
};
