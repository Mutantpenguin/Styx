#include "CGameInfo.hpp"

#include <fstream>

#include <json/json.h>

#include "../logger/CLogger.hpp"

#include "CFileSystem.hpp"


CGameInfo::CGameInfo( const std::string &p_gamedir ) :
	m_gamedir( p_gamedir )
{
	LOG( logDEBUG ) << "'gamedir' is: '" << m_gamedir << "'";

	const std::string gamefile = m_gamedir + CFileSystem::GetDirSeparator() + "gameinfo.json";

	std::ifstream fin( gamefile );

	if( fin )
	{
		Json::Value root;
		Json::Reader reader;
		if ( !reader.parse( fin, root ) )
		{
			LOG( logERROR ) << "failed to parse '" << gamefile << "' because of " << reader.getFormattedErrorMessages();
			throw std::exception();
		}

		const Json::Value entry = root[ "name_short" ];

		if( entry.empty() )
		{
			LOG( logERROR ) << "there is no definition of 'name_short' in the file '" << gamefile << "'";
			throw std::exception();
		}
		else if( entry.asString().empty() )
		{
			LOG( logERROR ) << "'name_short' in the file '" << gamefile << "' is empty";
			throw std::exception();
		}
		else
		{
			m_name = root[ "name" ].asString();

			m_name_short = root[ "name_short" ].asString();

			m_version = root[ "version"].asString();

			m_organisation = root[ "organisation"].asString();

			m_author = root[ "author" ].asString();

			m_author_email = root[ "author_email" ].asString();

			m_website = root[ "website" ].asString();

			m_icon = root[ "icon" ].asString();

			const Json::Value assets = root[ "assets" ];
			if(	assets.empty() )
			{
				LOG( logERROR ) << "no 'assets' specified in the file '" << gamefile << "'";
				throw std::exception();
			}
			else
			{
				m_assets.reserve( assets.size() );

				for( const Json::Value &asset : assets )
				{
					if( asset.asString().empty() )
					{
						LOG( logERROR ) << "empty 'asset' specified in the file '" << gamefile << "'";
						throw std::exception();
					}

					m_assets.push_back( asset.asString() );
				}
			}

			const Json::Value templates = root[ "templates" ];

			if(	templates.empty() )
			{
				LOG( logERROR ) << "no 'templates' specified in the file '" << gamefile << "'";
				throw std::exception();
			}
			else
			{
				m_templates.reserve( templates.size() );

				for( const Json::Value &templ : templates )
				{
					if( templ.asString().empty() )
					{
						LOG( logERROR ) << "empty 'template' specified in the file '" << gamefile << "'";
						throw std::exception();
					}

					m_templates.push_back( templ.asString() );
				}
			}

			m_background = root[ "background" ].asString();
		}
	}
	else
	{
		LOG( logERROR ) << "couldn't load '" << gamefile << "'";
		throw std::exception();
	}

	LOG( logINFO ) << "game is: '" << m_name << " " << m_version << "'";
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
