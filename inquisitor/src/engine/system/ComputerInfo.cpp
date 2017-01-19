#include "ComputerInfo.hpp"

#ifdef __linux__
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_cpuinfo.h>
#elif _WIN32
	#include <SDL.h>
	#include <SDL_cpuinfo.h>
#else
	#error "unsupported platform"
#endif


#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	// TODO still needed? #define WINVER 0x0501
	#include <tchar.h>
	#include <windows.h>
#else
	#include <limits>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <errno.h>
	#include <sys/sysinfo.h>
#endif

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/helper/String.hpp"

namespace ComputerInfo
{
	std::string OsName( void )
	{
		#ifdef WIN32
			std::string osversion = std::string( "unknown Windows" );

			OSVERSIONINFOEX	osinfo;
			SYSTEM_INFO		sysinfo;
			GetSystemInfo( &sysinfo );

			osinfo.dwOSVersionInfoSize = sizeof( osinfo );
			if( GetVersionEx( static_cast< OSVERSIONINFO* >( &osinfo ) ) )
			{
				switch( osinfo.dwPlatformId )
				{
				case VER_PLATFORM_WIN32_NT :
					if( 6 == osinfo.dwMajorVersion )
					{
						if( 0 == osinfo.dwMinorVersion )
						{
							if( VER_NT_WORKSTATION == osinfo.wProductType )
							{
								osversion = std::string( "Windows Vista " );
							}
							else
							{
								osversion = std::string( "Windows Server \"Longhorn\" " );
							}
						}
						else if( 1 == osinfo.dwMinorVersion )
						{
							osversion = std::string( "Windows 7 " );
						}
						else if( 2 == osinfo.dwMinorVersion )
						{
							osversion = std::string( "Windows 8 " );
						}
					}
					else if( 5 == osinfo.dwMajorVersion )
					{
						if( 0 == osinfo.dwMinorVersion )
						{
							osversion = std::string( "Microsoft Windows 2000 " );
						}
						else if( 1 == osinfo.dwMinorVersion )
						{
							osversion = std::string( "Microsoft Windows XP " );
						}
						else if( 2 == osinfo.dwMinorVersion )
						{
							if( GetSystemMetrics( 89 ) ) // stands for "SM_SERVERR2"
							{
								osversion = std::string( "Microsoft Windows Server 2003 \"R2\" ");
							}
							else if( ( VER_NT_WORKSTATION == osinfo.wProductType ) && ( PROCESSOR_ARCHITECTURE_AMD64 == sysinfo.wProcessorArchitecture ) )
							{
								osversion = std::string( "Microsoft Windows XP Professional x64 Edition ");
							}
							else
							{
								osversion = std::string( "Microsoft Windows Server 2003, " );
							}
						}
					}
					else if( osinfo.dwMajorVersion <= 4 )
					{
						osversion = std::string( "Microsoft Windows NT " );
					}

					if( ( VER_NT_WORKSTATION == osinfo.wProductType ) && ( PROCESSOR_ARCHITECTURE_AMD64 != sysinfo.wProcessorArchitecture ) )
					{
						if( 4 == osinfo.dwMajorVersion )
						{
							osversion += std::string( "Workstation 4.0 " );
						}
						else if( osinfo.wSuiteMask & VER_SUITE_PERSONAL )
						{
							osversion += std::string( "Home Edition " );
						}
						else
						{
							osversion += std::string( "Professional " );
						}
					}
					else if( ( VER_NT_SERVER == osinfo.wProductType )
							  ||
							  ( VER_NT_DOMAIN_CONTROLLER == osinfo.wProductType ) )
					{
						if( ( 5 == osinfo.dwMajorVersion ) && ( 2 == osinfo.dwMinorVersion ) )
						{
							if( PROCESSOR_ARCHITECTURE_IA64 == sysinfo.wProcessorArchitecture )
							{
								if( osinfo.wSuiteMask & VER_SUITE_DATACENTER )
								{
									osversion += std::string( "Datacenter Edition for Itanium-based Systems" );
								}
								else if( osinfo.wSuiteMask & VER_SUITE_ENTERPRISE )
								{
									osversion += std::string( "Enterprise Edition for Itanium-based Systems" );
								}
							}
							else if( PROCESSOR_ARCHITECTURE_AMD64 == sysinfo.wProcessorArchitecture )
							{
								if( osinfo.wSuiteMask & VER_SUITE_DATACENTER )
								{
									osversion += std::string( "Datacenter x64 Edition " );
								}
								else if( osinfo.wSuiteMask & VER_SUITE_ENTERPRISE )
								{
									osversion += std::string( "Enterprise x64 Edition " );
								}
								else
								{
									osversion += std::string( "Standard x64 Edition " );
								}
							}
							else
							{
								if( osinfo.wSuiteMask & VER_SUITE_DATACENTER )
								{
									osversion += std::string( "Datacenter Edition " );
								}
								else if( osinfo.wSuiteMask & VER_SUITE_ENTERPRISE )
								{
									osversion += std::string( "Enterprise Edition " );
								}
								else if( VER_SUITE_BLADE == osinfo.wSuiteMask )
								{
									osversion += std::string( "Web Edition " );
								}
								else
								{
									osversion += std::string( "Standard Edition " );
								}
							}
						}
						else if( ( 5 == osinfo.dwMajorVersion ) && ( 0 == osinfo.dwMinorVersion ) )
						{
							if( osinfo.wSuiteMask & VER_SUITE_DATACENTER )
							{
								osversion += std::string( "Datacenter Server " );
							}
							else if( osinfo.wSuiteMask & VER_SUITE_ENTERPRISE )
							{
								osversion += std::string( "Advanced Server " );
							}
							else
							{
								osversion += std::string( "Server " );
							}
						}
						else
						{
							if( osinfo.wSuiteMask & VER_SUITE_ENTERPRISE )
							{
								osversion += std::string("Server 4.0, Enterprise Edition " );
							}
							else
							{
								osversion += std::string( "Server 4.0 " );
							}
						}
					}
					else
					{
						HKEY hKey;
						TCHAR szProductType[ 80 ];
						DWORD dwBufLen = 80 * sizeof( TCHAR );
						LONG lRet;

						lRet = RegOpenKeyEx( HKEY_LOCAL_MACHINE, TEXT( "SYSTEM\\CurrentControlSet\\Control\\ProductOptions" ), 0, KEY_QUERY_VALUE, &hKey );
						if( lRet != ERROR_SUCCESS )
						{
							return FALSE;
						}
						lRet = RegQueryValueEx( hKey, TEXT( "ProductType" ), nullptr, nullptr, static_cast< LPBYTE >( szProductType ), &dwBufLen);
						RegCloseKey( hKey );

						if( ( lRet != ERROR_SUCCESS )
							||
							( dwBufLen > 80 * sizeof( TCHAR ) ) )
						{
							return FALSE;
						}

						if( 0 == lstrcmpi( TEXT( "WINNT" ), szProductType ) )
						{
							osversion += std::string(  "Workstation " );
						}
						if( 0 == lstrcmpi( TEXT( "LANMANNT" ), szProductType ) )
						{
							osversion += std::string(  "Server " );
						}
						if( 0 == lstrcmpi( TEXT( "SERVERNT" ), szProductType ) )
						{
							osversion += std::string(  "Advanced Server " );
						}
						osversion += std::string(  "%d.%d ", osinfo.dwMajorVersion, osinfo.dwMinorVersion );
					}

					// Display service pack (if any) and build number.
					if( ( 4 == osinfo.dwMajorVersion ) && ( 0 == lstrcmpi( osinfo.szCSDVersion, TEXT( "Service Pack 6" ) ) ) )
					{
						HKEY hKey;

						// Test for SP6 versus SP6a.
						if( ERROR_SUCCESS == RegOpenKeyEx( HKEY_LOCAL_MACHINE, TEXT( "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Hotfix\\Q246009" ), 0, KEY_QUERY_VALUE, &hKey ) )
						{
							osversion += std::string(  "Service Pack 6a (Build %d)\n", osinfo.dwBuildNumber & 0xFFFF );
						}
						else // Windows NT 4.0 prior to SP6a
						{
							std::stringstream strm;
							strm << ( osinfo.dwBuildNumber & 0xFFFF );
							osversion += std::string( osinfo.szCSDVersion ) + std::string( " (Build " ) + strm.str() + std::string( ")\n"  );
						}

						RegCloseKey( hKey );
					}
					else // not Windows NT 4.0
					{
						std::stringstream strm;
						strm << (osinfo.dwBuildNumber & 0xFFFF);
						osversion += std::string( osinfo.szCSDVersion ) + std::string( " (Build " ) + strm.str() + std::string( ")"  );
					}

					break;

				case VER_PLATFORM_WIN32_WINDOWS :
					if( 4 == osinfo.dwMajorVersion )
					{
						if( 0 == osinfo.dwMinorVersion )
						{
							osversion = "Microsoft Windows 95 ";
							if( ( 'B' == osinfo.szCSDVersion[ 1 ] )
								||
								( 'C' == osinfo.szCSDVersion[ 1 ] ) )
							{
								osversion += std::string( "OSR2 " );
							}
						}
						else if( 10 == osinfo.dwMinorVersion )
						{
							osversion = "Microsoft Windows 98 ";
							if( ( 'A' == osinfo.szCSDVersion[ 1 ] )
								||
								( 'B' == osinfo.szCSDVersion[ 1 ] ) )
							{
								osversion += std::string( "SE " );
							}
						}
						else if( 90 == osinfo.dwMinorVersion )
						{
							osversion = "Microsoft Windows Millenium Edition ";
						}
					}
					break;

				case VER_PLATFORM_WIN32s :
					osversion = "Microsoft Win32s";
					break;
				}
			}
		#else // linux
			std::string osversion = std::string( "unknown Linux" );

			const std::string lsbReleaseFilename { "/etc/lsb-release" };
			FILE *file_lsb_release_exists = fopen( lsbReleaseFilename.c_str(), "r" );
			if( nullptr != file_lsb_release_exists )
			{
				fclose( file_lsb_release_exists );

				const std::string lsbReleaseCommand { "lsb_release -drs" };
				FILE *file_release = popen( lsbReleaseCommand.c_str(), "r" );
				if( nullptr != file_release )
				{
					char buffer_release[ 128 ];

					fgets( buffer_release, 128, file_release );
					pclose( file_release );

					buffer_release[ strlen( buffer_release ) - 1 ] = 0;

					osversion = std::string( buffer_release );

					const std::string kernelVersionCommand { "uname -rmo" };
					FILE *file_kernel = popen( kernelVersionCommand.c_str(), "r" );
					if( nullptr != file_kernel )
					{
						char buffer_kernel[ 128 ];
						fgets( buffer_kernel, 128, file_kernel );
						pclose( file_kernel );

						buffer_kernel[ strlen( buffer_kernel ) - 1 ] = 0;

						osversion += std::string( " Kernel " ) + std::string( buffer_kernel );
					}
					else
					{
						logWARNING( "'{0}' couldn't be run", kernelVersionCommand );
					}
				}
				else
				{
					logWARNING( "'{0}' couldn't be run", lsbReleaseCommand );
				}
			}
			else
			{
				logWARNING( "'{0}' doesn't seem to exist", lsbReleaseFilename );
			}
		#endif

		return( osversion );
	}

	int SystemMemoryMiB( void )
	{
		return( SDL_GetSystemRAM() );
	}

	int ProcessorCount( void )
	{
		return( SDL_GetCPUCount() );
	}

	std::string ProcessorInfo( void )
	{
		// TODO with SDL 2.x we can use the following functions to get CPU-Information
		// SDL_GetCPUType();
		// SDL_GetCPUName();

		#ifdef WIN32
			char	value[ 1024 ];
			DWORD	valueSize;
			HKEY	hKey;

			std::string processor{ "unknown" };

			if( ERROR_SUCCESS == RegOpenKeyEx( HKEY_LOCAL_MACHINE, "Hardware\\Description\\System\\CentralProcessor\\0", 0, KEY_QUERY_VALUE, &hKey ) )
			{
				// get processor name
				valueSize = 1024;
				if( ERROR_SUCCESS == RegQueryValueEx( hKey, _T( "ProcessorNameString" ), nullptr, nullptr, static_cast< LPBYTE >( &value ), &valueSize ) )
				{
					processor = value;
				}
				else
				{
					processor = "UnknownProc";
				}

				processor += " / ";

				// get processor identifier
				valueSize = 1024;
				if( ERROR_SUCCESS == RegQueryValueEx( hKey, _T( "Identifier" ), nullptr, nullptr, static_cast< LPBYTE >( &value ), &valueSize ) )
				{
					processor += value;
				}
				else
				{
					processor += "UnknownIdentifier";
				}

				processor += " / ";

				// get processor vendor
				valueSize = 1024;
				if( ERROR_SUCCESS == RegQueryValueEx( hKey, _T( "VendorIdentifier" ), nullptr, nullptr, static_cast< LPBYTE >( &value ), &valueSize ) )
				{
					processor += value;
				}
				else
				{
					processor += "UnknownVendor";
				}

				processor += " / ";

				// get processor frequence
				valueSize = 1024;
				if( ERROR_SUCCESS == RegQueryValueEx( hKey, _T( "~MHz" ), nullptr, nullptr, static_cast< LPBYTE >( &value ), &valueSize ) )
				{
					processor += std::to_string( *static_cast< int* >( value ), value, 10 );
					processor += "MHz";

				}
				else
				{
					processor += "UnknownFreq";
				}
			}

			return( String::trim( processor ) );

			RegCloseKey( hKey );
		#else // linux
			std::string model_name;
			std::string cpufamily;
			std::string model;
			std::string stepping;
			std::string vendor_id;
			std::string mhz;

			FILE *file_cpuinfo = fopen( "/proc/cpuinfo", "r" );
			if( nullptr != file_cpuinfo )
			{
				char buffer[ 128 ];

				while( fgets( buffer, 128, file_cpuinfo ) )
				{
					buffer[ strlen( buffer ) - 1 ] = 0;
					std::string std_buffer( buffer );
					if( std_buffer.substr( 0, 10 ) == std::string( "model name" ) )
					{
						model_name = String::trim( std_buffer.substr( std_buffer.find( ":" ) + 2, std_buffer.length() ) );
					}
					else if( std_buffer.substr( 0, 9 ) == std::string( "vendor_id" ) )
					{
						vendor_id = std_buffer.substr( std_buffer.find( ":" ) + 2, std_buffer.length() );
					}
					else if( std_buffer.substr( 0, 10 ) == std::string( "cpu family" ) )
					{
						cpufamily = std_buffer.substr( std_buffer.find( ":" ) + 2, std_buffer.length() );
					}
					else if( std_buffer.substr( 0, 5 ) == std::string( "model" ) )
					{
						model = std_buffer.substr( std_buffer.find( ":" ) + 2, std_buffer.length() );
					}
					else if( std_buffer.substr( 0, 8 ) == std::string( "stepping" ) )
					{
						stepping = std_buffer.substr( std_buffer.find( ":" ) + 2, std_buffer.length() );
					}
					else if( std_buffer.substr( 0, 7 ) == std::string( "cpu MHz" ) )
					{
						std::string mhz2 = std_buffer.substr( std_buffer.find( ":" ) + 2, std_buffer.length() );
						mhz = mhz2.erase( mhz2.find_last_not_of( "0123456789" ) );
					}
				}

				fclose( file_cpuinfo );

				return( model_name + std::string( " / Family " ) + cpufamily + std::string( " Model " ) + model + std::string( " Stepping " ) + stepping + std::string( " / " ) + vendor_id + std::string( " / " ) + mhz + std::string( "MHz" ) );
			}

			return( "unknown" );
		#endif
	}

	std::string CPUFeatures( void )
	{
		std::string cpuFeatures;

		if( SDL_HasRDTSC() )
		{
			cpuFeatures += "RDTSC ";
		}

		if( SDL_HasAltiVec() )
		{
			cpuFeatures += "AltiVec ";
		}

		if( SDL_HasMMX() )
		{
			cpuFeatures += "MMX ";
		}

		if( SDL_Has3DNow() )
		{
			cpuFeatures += "3DNow ";
		}

		if( SDL_HasSSE() )
		{
			cpuFeatures += "SSE ";
		}

		if( SDL_HasSSE2() )
		{
			cpuFeatures += "SSE2 ";
		}

		if( SDL_HasSSE3() )
		{
			cpuFeatures += "SSE3 ";
		}

		if( SDL_HasSSE41() )
		{
			cpuFeatures += "SSE41 ";
		}

		if( SDL_HasSSE42() )
		{
			cpuFeatures += "SSE42 ";
		}

		if( SDL_HasAVX() )
		{
			cpuFeatures += "AVX";
		}

		return( cpuFeatures );
	}
}
