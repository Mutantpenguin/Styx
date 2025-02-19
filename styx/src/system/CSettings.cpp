#include "CSettings.hpp"

#include "external/json/json.hpp"
using json = nlohmann::json;

#include "src/core/Types.hpp"

#include "src/logger/CLogger.hpp"

#include "src/core/StyxException.hpp"


CSettings::CSettings( const CFileSystem &p_filesystem, const std::string &settingsfile )
{
	const std::string filename = settingsfile.empty() ? "settings.json" : settingsfile;

	logINFO( "using settings-file '{0}'", filename );

	if( !p_filesystem.Exists( filename ) )
	{
		logWARNING( "settings-file '{0}' does not exist", filename );
	}
	else
	{
		const auto settings_root = [&]() -> json {
			try
			{
				return( json::parse( p_filesystem.LoadFileToString( filename ) ) );
			}
			catch( json::parse_error &e )
			{
				THROW_STYX_EXCEPTION( "failed to parse settings-file '{0}' because of: {1}", filename, e.what() )
			}
		} ();

		const auto renderer_root = settings_root.find( "renderer" );
		if( std::end( settings_root ) == renderer_root )
		{
			logWARNING( "'settings.renderer' not found" );
		}
		else
		{
			const auto window_root = renderer_root->find( "window" );
			if( renderer_root->end() == window_root )
			{
				logWARNING( "'settings.renderer.window' not found" );
			}
			else
			{
				const auto width = window_root->find( "width" );
				if( window_root->end() == width )
				{
					logWARNING( "'settings.renderer.window.width' not found" );
				}
				else
				{
					renderer.window.size.width = width->get<u32>();
				}

				const auto height = window_root->find( "height" );
				if( window_root->end() == height )
				{
					logERROR( "'settings.renderer.window.height' not found" );
				}
				else
				{
					renderer.window.size.height = height->get<u32>();
				}

				renderer.window.aspect_ratio = static_cast<f16>( renderer.window.size.width ) / static_cast<f16>( renderer.window.size.height );

				const auto display = window_root->find( "display" );
				if( window_root->end() == display )
				{
					logWARNING( "'settings.renderer.window.display' not found" );
				}
				else
				{
					renderer.window.display = display->get<int>();
				}

				const auto fullsreen = window_root->find( "fullscreen" );
				if( window_root->end() == fullsreen )
				{
					logWARNING( "'settings.renderer.window.fullscreen' not found" );
				}
				else
				{
					renderer.window.fullscreen = fullsreen->get<bool>();
				}

				const auto vsync = window_root->find( "vsync" );
				if( window_root->end() == vsync )
				{
					logWARNING( "'settings.renderer.window.vsync' not found" );
				}
				else
				{
					renderer.window.vsync = vsync->get<bool>();
				}

				const auto gamma = window_root->find( "gamma" );
				if( window_root->end() == gamma )
				{
					logWARNING( "'settings.renderer.window.gamma' not found" );
				}
				else
				{
					renderer.window.gamma = gamma->get<f16>();
				}

				const auto antialiasing = window_root->find( "antialiasing" );
				if( window_root->end() == antialiasing )
				{
					logWARNING( "'settings.renderer.window.antialiasing' not found" );
				}
				else
				{
					renderer.window.antialiasing = antialiasing->get<bool>();
				}
			}

			const auto textures_root = renderer_root->find( "textures" );
			if( renderer_root->end() == textures_root )
			{
				logWARNING( "'settings.renderer.textures' not found" );
			}
			else
			{
				const auto anisotropic = textures_root->find( "anisotropic" );
				if( textures_root->end() == anisotropic )
				{
					logWARNING( "'settings.renderer.textures.anisotropic' not found" );
				}
				else
				{
					renderer.textures.anisotropic = anisotropic->get<u8>();
				}
			}

			const auto screenshot_root = renderer_root->find( "screenshot" );
			if( renderer_root->end() == screenshot_root )
			{
				logWARNING( "'settings.renderer.screenshot' not found" );
			}
			else
			{
				const auto format = screenshot_root->find( "format" );
				if( screenshot_root->end() == format )
				{
					logWARNING( "'settings.renderer.screenshot.format' not found" );
				}
				else
				{
					renderer.screenshot.format = format->get<std::string>();
				}
			}
		}

		const auto audio_root = settings_root.find( "audio" );
		if( std::end( settings_root ) == audio_root )
		{
			logWARNING( "'settings.audio' not found" );
		}
		else
		{
			const auto volume = audio_root->find( "volume" );
			if( audio_root->end() == volume )
			{
				logWARNING( "'settings.audio.volume' not found" );
			}
			else
			{
				audio.volume = volume->get<f16>();
			}

			const auto buffer_size = audio_root->find( "buffer_size" );
			if( audio_root->end() == buffer_size )
			{
				logWARNING( "'settings.audio.buffer_size' not found" );
			}
			else
			{
				audio.buffer_size = buffer_size->get<u16>();
			}
		}

		const auto input_root = settings_root.find( "input" );
		if( std::end( settings_root ) == input_root )
		{
			logWARNING( "'settings.input' not found" );
		}
		else
		{
			const auto controller_file = input_root->find( "controller_file" );
			if( input_root->end() == controller_file )
			{
				logWARNING( "'settings.input.controller_file' not found" );
			}
			else
			{
				input.controller_file = controller_file->get<std::string>();
			}
		}
	}
}
