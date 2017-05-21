#include "CGameInfo.hpp"

#include <fstream>

#include "src/ext/json/json.hpp"
using json = nlohmann::json;

#include "src/engine/logger/CLogger.hpp"

#include "CFileSystem.hpp"


CGameInfo::CGameInfo( const std::string &p_gamedir ) :
	m_gamedir( p_gamedir )
{
	logDEBUG( "'gamedir' is: '{0}'", m_gamedir );

	const std::string gamefile = m_gamedir + CFileSystem::GetDirSeparator() + "gameinfo.json";

	std::ifstream fin( gamefile );

	if( fin )
	{
		const auto root = [&]() -> json {
			try
			{
				return( json::parse( fin ) );
			}
			catch( json::parse_error &e )
			{
				logERROR( "failed to parse '{0}' because of {1}", gamefile, e.what() );
				throw Exception();
			}
		} ();

		const auto name_short = root.find( "name_short" );
		if( ( std::end( root ) == name_short ) || name_short->empty() )
		{
			logERROR( "there is no definition of 'name_short' in the file '{0}'", gamefile );
			throw Exception();
		}
		else
		{
			m_name_short = name_short->get<std::string>();
		}

		const auto name = root.find( "name" );
		if( ( std::end( root ) == name ) || name->empty() )
		{
			logERROR( "there is no definition of 'name' in the file '{0}'", gamefile );
			throw Exception();
		}
		else
		{
			m_name = name->get<std::string>();
		}

		const auto version = root.find( "version" );
		if( ( std::end( root ) == version ) || version->empty() )
		{
			logERROR( "there is no definition of 'version' in the file '{0}'", gamefile );
			throw Exception();
		}
		else
		{
			m_version = version->get<std::string>();
		}

		m_organisation = root.value( "organisation", "" );

		m_author = root.value( "author", "" );

		m_author_email = root.value( "author_email", "" );

		m_website = root.value( "website", "" );

		const auto icon = root.find( "icon" );
		if( ( std::end( root ) == icon ) || icon->empty() )
		{
			logERROR( "there is no definition of 'icon' in the file '{0}'", gamefile );
			throw Exception();
		}
		else
		{
			m_icon = icon->get<std::string>();
		}

		const auto assets = root.find( "assets" );
		if(	( std::end( root ) == assets ) || ( assets->empty() ) )
		{
			logERROR( "no 'assets' specified in the file '{0}'", gamefile );
			throw Exception();
		}
		else
		{
			m_assets.reserve( assets->size() );

			for( const auto &asset : (*assets) )
			{
				const auto assetString = asset.get<std::string>();

				if( assetString.empty() )
				{
					logERROR( "empty 'asset' specified in the file '{0}'", gamefile );
					throw Exception();
				}

				m_assets.push_back( assetString );
			}
		}

		const auto templates = root.find( "templates" );
		if( ( std::end( root ) == templates ) || ( templates->empty() ) )
		{
			logERROR( "no 'templates' specified in the file '{0}'", gamefile );
			throw Exception();
		}
		else
		{
			m_templates.reserve( templates->size() );

			for( const auto &templ : (*templates) )
			{
				const auto templateString = templ.get<std::string>();

				if( templateString.empty() )
				{
					logERROR( "empty 'template' specified in the file '{0}'", gamefile );
					throw Exception();
				}

				m_templates.push_back( templateString );
			}
		}

		m_menu_background = root.value( "menu_background", "" );
	}
	else
	{
		logERROR( "couldn't load '{0}'", gamefile );
		throw Exception();
	}

	logINFO( "game is: '{0} {1}'", m_name, m_version );
}

const std::string &CGameInfo::GetDir( void ) const
{
	return( m_gamedir );
}

const std::string &CGameInfo::GetName( void ) const
{
	return( m_name );
}

const std::string &CGameInfo::GetShortName( void ) const
{
	return( m_name_short );
}

const std::string &CGameInfo::GetVersion( void ) const
{
	return( m_version );
}

const std::string &CGameInfo::GetOrganisation( void ) const
{
	return( m_organisation );
}

const std::string &CGameInfo::GetAuthor( void ) const
{
	return( m_author );
}

const std::string &CGameInfo::GetAuthorEmail( void ) const
{
	return( m_author_email );
}

const std::string &CGameInfo::GetWebsite( void ) const
{
	return( m_website );
}

const std::string &CGameInfo::GetIconPath( void ) const
{
	return( m_icon );
}

const std::vector< std::string > &CGameInfo::GetAssets( void ) const
{
	return( m_assets );
}

const std::vector< std::string > &CGameInfo::GetTemplates( void ) const
{
	return( m_templates );
}
