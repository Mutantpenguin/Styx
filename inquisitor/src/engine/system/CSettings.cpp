#include "CSettings.hpp"

#include <json/json.h>

#include "src/engine/logger/CLogger.hpp"


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
		Json::Reader reader;
		Json::Value settings_root;

		if( !reader.parse( p_filesystem.LoadFileToString( filename ), settings_root ) )
		{
			logWARNING( "failed to parse settings-file '{0}' because of: {1}", filename, reader.getFormattedErrorMessages() );
		}
		else
		{
			const Json::Value renderer_root = settings_root[ "renderer" ];
			if( !renderer_root.empty() )
			{
				const Json::Value window_root = renderer_root[ "window" ];
				if( !window_root.empty() )
				{
					const Json::Value width = window_root[ "width" ];
					if( width.empty() )
					{
						logWARNING( "'settings.renderer.window.width' not found" );
					}
					else
					{
						renderer.window.size.width = width.asUInt();
					}

					const Json::Value height = window_root[ "height" ];
					if( height.empty() )
					{
						logWARNING( "'settings.renderer.window.height' not found" );
					}
					{
						renderer.window.size.height = height.asUInt();
					}

					renderer.window.aspect_ratio = static_cast< float >( renderer.window.size.width ) / static_cast< float >( renderer.window.size.height );

					const Json::Value fullsreen = window_root[ "fullscreen" ];
					if( fullsreen.empty() )
					{
						logWARNING( "'settings.renderer.window.fullscreen' not found" );
					}
					else
					{
						renderer.window.fullscreen = fullsreen.asBool();
					}

					const Json::Value vsync = window_root[ "vsync" ];
					if( vsync.empty() )
					{
						logWARNING( "'settings.renderer.window.vsync' not found" );
					}
					else
					{
						renderer.window.vsync = vsync.asBool();
					}

					const Json::Value gamma = window_root[ "gamma" ];
					if( gamma.empty() )
					{
						logWARNING( "'settings.renderer.window.gamma' not found" );
					}
					else
					{
						renderer.window.gamma = gamma.asDouble();
					}

					const Json::Value antialiasing = window_root[ "antialiasing" ];
					if( antialiasing.empty() )
					{
						logWARNING( "'settings.renderer.window.antialiasing' not found" );
					}
					else
					{
						renderer.window.antialiasing = antialiasing.asBool();
					}
				}
				else
				{
					logWARNING( "'settings.renderer.window' not found" );
				}

				const Json::Value textures_root = renderer_root[ "textures" ];
				if( !textures_root.empty() )
				{
					const Json::Value anisotropic = textures_root[ "anisotropic" ];
					if( anisotropic.empty() )
					{
						logWARNING( "'settings.renderer.textures.anisotropic' not found" );
					}
					else
					{
						renderer.textures.anisotropic = anisotropic.asUInt();
					}

					const Json::Value picmip = textures_root[ "picmip" ];
					if( picmip.empty() )
					{
						logWARNING( "'settings.renderer.textures.picmip' not found" );
					}
					else
					{
						renderer.textures.picmip = picmip.asUInt();
					}
				}
				else
				{
					logWARNING( "'settings.renderer.textures' not found" );
				}

				const Json::Value screenshot_root = renderer_root[ "screenshot" ];
				if( !screenshot_root.empty() )
				{
					const Json::Value format = screenshot_root[ "format" ];
					if( format.empty() )
					{
						logWARNING( "'settings.renderer.screenshot.format' not found" );
					}
					else
					{
						renderer.screenshot.format = format.asString();
					}

					const Json::Value scale_factor = screenshot_root[ "scale_factor" ];
					if( scale_factor.empty() )
					{
						logWARNING( "'settings.renderer.screenshot.scale_factor' not found" );
					}
					else
					{
						renderer.screenshot.scale_factor = scale_factor.asDouble();
					}
				}
				else
				{
					logWARNING( "'settings.renderer.screenshot' not found" );
				}
			}
			else
			{
				logWARNING( "'settings.renderer' not found" );
			}

			const Json::Value sound_root = settings_root[ "sound" ];
			if( !sound_root.empty() )
			{
				const Json::Value buffer_size = sound_root[ "buffer_size" ];
				if( buffer_size.empty() )
				{
					logWARNING( "'settings.sound.buffer_size' not found" );
				}
				else
				{
					sound.buffer_size = buffer_size.asUInt();
				}
			}
			else
			{
				logWARNING( "'settings.sound' not found" );
			}

			const Json::Value input_root = settings_root[ "input" ];
			if( !input_root.empty() )
			{
				const Json::Value controller_file = input_root[ "controller_file" ];
				if( controller_file.empty() )
				{
					logWARNING( "'settings.input.controller_file' not found" );
				}
				else
				{
					input.controller_file = controller_file.asString();
				}
			}
			else
			{
				logWARNING( "'settings.input' not found" );
			}
		}
	}
}
