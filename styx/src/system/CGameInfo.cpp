#include "CGameInfo.hpp"

#include <fstream>

#include "external/json/json.hpp"
using json = nlohmann::json;

#include "src/logger/CLogger.hpp"

#include "CFileSystem.hpp"

#include "src/core/StyxException.hpp"

const std::string CGameInfo::gameinfoFilename { "gameinfo.json" };

CGameInfo::CGameInfo( const std::filesystem::path &gamePath ) :
	m_gamePath( gamePath )
{
	if( m_gamePath.has_filename() )
	{
		THROW_STYX_EXCEPTION( "gamepath '{0}' contains a filename", m_gamePath.generic_string() );
	}

	logINFO( "the path of the game is: '{0}'", m_gamePath.generic_string() );

	const std::filesystem::path gameInfoPath = m_gamePath / gameinfoFilename;

	std::ifstream fin( gameInfoPath );

	if( fin.good() )
	{
		const auto root = [&]() -> json {
			try
			{
				return( json::parse( fin ) );
			}
			catch( json::parse_error &e )
			{
				THROW_STYX_EXCEPTION( "failed to parse '{0}' because of {1}", gameInfoPath.generic_string(), e.what() )
			}
		} ();

		const auto name_short = root.find( "name_short" );
		if( ( std::end( root ) == name_short ) || name_short->empty() )
		{
			THROW_STYX_EXCEPTION( "there is no definition of 'name_short' in the file '{0}'", gameInfoPath.generic_string() )
		}
		else
		{
			m_name_short = name_short->get<std::string>();
		}
		
		m_info = root.value( "info", "" );

		const auto name = root.find( "name" );
		if( ( std::end( root ) == name ) || name->empty() )
		{
			THROW_STYX_EXCEPTION( "there is no definition of 'name' in the file '{0}'", gameInfoPath.generic_string() )
		}
		else
		{
			m_name = name->get<std::string>();
		}

		const auto version = root.find( "version" );
		if( ( std::end( root ) == version ) || version->empty() )
		{
			THROW_STYX_EXCEPTION( "there is no definition of 'version' in the file '{0}'", gameInfoPath.generic_string() )
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
			THROW_STYX_EXCEPTION( "there is no definition of 'icon' in the file '{0}'", gameInfoPath.generic_string() )
		}
		else
		{
			m_icon = icon->get<std::string>();
		}

		const auto assets = root.find( "assets" );
		if(	( std::end( root ) == assets ) || ( assets->empty() ) )
		{
			THROW_STYX_EXCEPTION( "no 'assets' specified in the file '{0}'", gameInfoPath.generic_string() )
		}
		else
		{
			m_assets.reserve( assets->size() );

			for( const auto &asset : (*assets) )
			{
				const auto assetString = asset.get<std::string>();

				if( assetString.empty() )
				{
					THROW_STYX_EXCEPTION( "empty 'asset' specified in the file '{0}'", gameInfoPath.generic_string() )
				}

				m_assets.push_back( assetString );
			}
		}

		const auto templates = root.find( "templates" );
		if( ( std::end( root ) == templates ) || ( templates->empty() ) )
		{
			THROW_STYX_EXCEPTION( "no 'templates' specified in the file '{0}'", gameInfoPath.generic_string() )
		}
		else
		{
			m_templates.reserve( templates->size() );

			for( const auto &templ : (*templates) )
			{
				const auto templateString = templ.get<std::string>();

				if( templateString.empty() )
				{
					THROW_STYX_EXCEPTION( "empty 'template' specified in the file '{0}'", gameInfoPath.generic_string() )
				}

				m_templates.push_back( templateString );
			}
		}

		m_menu_background = root.value( "menu_background", "" );
	}
	else
	{
		THROW_STYX_EXCEPTION( "couldn't load '{0}'", gameInfoPath.generic_string() )
	}

	logINFO( "game is: '{0} {1}'", m_name, m_version );
	
	if( m_info.length() > 0 )
	{
		logINFO( m_info );
	}
}

const std::filesystem::path &CGameInfo::GetPath() const
{
	return( m_gamePath );
}

const std::string &CGameInfo::GetName() const
{
	return( m_name );
}

const std::string &CGameInfo::GetShortName() const
{
	return( m_name_short );
}

const std::string &CGameInfo::GetInfo() const
{
	return( m_info );
}

const std::string &CGameInfo::GetVersion() const
{
	return( m_version );
}

const std::string &CGameInfo::GetOrganisation() const
{
	return( m_organisation );
}

const std::string &CGameInfo::GetAuthor() const
{
	return( m_author );
}

const std::string &CGameInfo::GetAuthorEmail() const
{
	return( m_author_email );
}

const std::string &CGameInfo::GetWebsite() const
{
	return( m_website );
}

const std::string &CGameInfo::GetIconPath() const
{
	return( m_icon );
}

const std::vector< std::string > &CGameInfo::GetAssets() const
{
	return( m_assets );
}

const std::vector< std::string > &CGameInfo::GetTemplates() const
{
	return( m_templates );
}
