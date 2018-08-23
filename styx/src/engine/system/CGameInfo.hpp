#ifndef CGAMEINFO_HPP
#define CGAMEINFO_HPP

#include <exception>
#include <string>
#include <vector>

class CGameInfo final
{
public:
	explicit CGameInfo( const std::string &p_gamedir  );

	const std::string &GetDir( void ) const;

	const std::string &GetName( void ) const;
	const std::string &GetShortName( void ) const;
	const std::string &GetInfo( void ) const; // TODO print this out into the console!
	const std::string &GetVersion( void ) const;
	const std::string &GetOrganisation( void ) const;
	const std::string &GetAuthor( void ) const;
	const std::string &GetAuthorEmail( void ) const;
	const std::string &GetWebsite( void ) const;

	const std::string &GetIconPath( void ) const;

	const std::vector< std::string > &GetAssets( void ) const;
	const std::vector< std::string > &GetTemplates( void ) const;

	class Exception: public std::exception
	{
	public:
		explicit Exception( void ) {}

		virtual ~Exception() throw() {}
	};

private:
	CGameInfo( const CGameInfo &rhs ) = delete;
	CGameInfo& operator = ( const CGameInfo &rhs ) = delete;

	static const std::string gameinfoFilename;

	const std::string m_gamedir;

	std::string m_name;
	std::string m_name_short;
	std::string m_info;
	std::string m_version;
	std::string m_organisation;
	std::string m_author;
	std::string m_author_email;
	std::string m_website;

	std::string m_icon;

	std::vector< std::string > m_assets;
	std::vector< std::string > m_templates;

	std::string m_menu_background;
};

#endif // CGAMEINFO_HPP
