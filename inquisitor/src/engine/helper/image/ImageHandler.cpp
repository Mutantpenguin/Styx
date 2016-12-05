#include "ImageHandler.hpp"

#include <FreeImagePlus.h>

#include "src/engine/logger/CLogger.hpp"

#include "../../math/Math.hpp"

#include "../CFreeImageWrapper.hpp"

namespace ImageHandler
{
	/**	Loads an bitmap using FreeImage into a CImage.
		If necessary it gets rescaled to maxSize
	*/
	std::shared_ptr< CImage > Load( const CFileSystem &p_filesystem, const std::string &path, const std::uint32_t maxSize, const unsigned int picMip, const bool flipVertically )
	{
		if( !p_filesystem.Exists( path ) )
		{
			logWARNING( "image '{0}' does not exist", path );
			return( nullptr );
		}

		CFileSystem::File *f = p_filesystem.Open( path.c_str(), CFileSystem::e_openmode::READ );
		if( nullptr != f )
		{
			fipImage image;

			image.loadFromHandle( &CFreeImageWrapper::Get( p_filesystem ), static_cast< fi_handle >( f ), 0 );

			p_filesystem.Close( f );

			if( image.isValid() )
			{
				if( image.accessPixels() == nullptr )
				{
					logWARNING( "image '{0}' only consists of metadata and no pixels", path );
					return( nullptr );
				}

				if( image.getPalette() != nullptr )
				{
					logWARNING( "palettized image '{0}' is not supported", path );
					return( nullptr );
				}

				const CSize originalSize { image.getWidth(), image.getHeight() };
				const unsigned int bpp				= image.getBitsPerPixel();

				if(	!Math::IsPowerOfTwo( originalSize.width )
					||
					!Math::IsPowerOfTwo( originalSize.height ) )
				{
					logWARNING( "the size of image '{0}' is not a power of two", path );

					return( nullptr );
				}

				// rescale image if necessary
				CSize resizedSize { originalSize };
				bool resize = false;
				if( 0 != picMip )
				{
					resizedSize.width	>>= picMip;
					resizedSize.height	>>= picMip;

					resize = true;
				}

				if(	( resizedSize.width > maxSize )
					||
					( resizedSize.height > maxSize ) )
				{
					logWARNING( "image '{0}' has to be scaled down because it's bigger than the allowed max size of '{1}' pixels", path, maxSize );
					// scale both axis down equally
					while(	( resizedSize.width > maxSize )
							||
							( resizedSize.height > maxSize ) )
					{
						resizedSize.width	>>= 1;
						resizedSize.height	>>= 1;
					}
					resize = true;
				}

				// if width or height are below 1 we can't rescale
				resizedSize.width	= std::max( static_cast< std::uint32_t >( 1 ), resizedSize.width );
				resizedSize.height	= std::max( static_cast< std::uint32_t >( 1 ), resizedSize.height );

				if( resize )
				{
					if( !image.rescale( resizedSize.width, resizedSize.height, FILTER_BSPLINE ) )
					{
						logWARNING( "failed to rescale image '{0}'", path );

						return( nullptr );
					}
				}

				if( flipVertically )
				{
					FreeImage_FlipVertical( image );
				}

				const bool alpha = image.isTransparent();

				const int pitch = image.getScanWidth();

				std::unique_ptr< CImage::PixelBuffer > imageData = std::make_unique< CImage::PixelBuffer >( pitch * resizedSize.height );

				std::copy( image.accessPixels(), image.accessPixels() + ( pitch * resizedSize.height ), imageData->begin() );

				return( std::make_shared< CImage >( resizedSize, originalSize, alpha, bpp, pitch, std::move( imageData ) ) );
			}
			else
			{
				logWARNING( "failed to load '{0}'", path );
			}
		}
		else
		{
			logWARNING( "failed to open '{0}'", path );
		}

		return( nullptr );
	}

	bool Save( const CFileSystem &p_filesystem, const std::shared_ptr< const CImage > &image, const float scale_factor, const std::string &format, const std::string &path )
	{
		FIBITMAP *bitmap = FreeImage_ConvertFromRawBits( const_cast< BYTE* >( image->RawPixelData() ), image->Size().width, image->Size().height, image->Size().width * 3, image->BPP(), FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK );
		if( nullptr == bitmap )
		{
			logWARNING( "unable to create FIBITMAP from CImage" );
			return( false );
		}
		else
		{
			fipImage fiImage;
			fiImage = bitmap;

			if( scale_factor < 1.0f )
			{
				logDEBUG( "resizing image by '{0}'", scale_factor );

				if( !fiImage.rescale( image->Size().width * scale_factor, image->Size().height * scale_factor, FILTER_BSPLINE ) )
				{
					logWARNING( "failed to rescale image" );
					return( false );
				}
			}

			FREE_IMAGE_FORMAT fiFormat;
			int flags;
			if( format == "png" )
			{
				fiFormat	= FIF_PNG;
				flags		= PNG_DEFAULT;
			}
			else if( ( format == "jpg" ) || ( format == "jpeg" ) )
			{
				fiFormat	= FIF_JPEG;
				flags		= JPEG_DEFAULT;
			}
			else
			{
				logWARNING( "unknown image-format '{0}', using default 'png' for now", format );
				fiFormat	= FIF_PNG;
				flags		= PNG_DEFAULT;
			}

			CFileSystem::File *f = p_filesystem.Open( path, CFileSystem::e_openmode::WRITE );

			if( nullptr == f )
			{
				logERROR( "File '{0}' couldn't be opened for writing because of: {1}", path, p_filesystem.GetLastError() );
				return( false );
			}

			fiImage.saveToHandle( fiFormat, &CFreeImageWrapper::Get( p_filesystem ), static_cast< fi_handle >( f ), flags );

			p_filesystem.Close( f );

			return( true );
		}
	}

	std::shared_ptr< CImage > GenerateCheckerImage( const CSize &size )
	{
		if( !Math::IsPowerOfTwo( size.width ) )
		{
			logWARNING( "width '{0}' is not a power of two", size.width );
			return( nullptr );
		}
		else if( !Math::IsPowerOfTwo( size.height ) )
		{
			logWARNING( "height '{0}' is not a power of two", size.height );
			return( nullptr );
		}
		else
		{
			std::unique_ptr< CImage::PixelBuffer > checkerImageData = std::make_unique< CImage::PixelBuffer >( size.width * size.height * 4 );

			for( unsigned int i = 0; i < size.height; ++i )
			{
				for( unsigned int j = 0; j < size.width; ++j )
				{
					const unsigned int c = ( ( ( i & 0x8 ) == 0 ) ^ ( ( j & 0x8 ) == 0  ) ) * 255;
					const unsigned int index = ( ( i * size.width ) * 4 ) + ( j * 4 );
					checkerImageData->at( index + 0 ) = static_cast< unsigned char >( c );		// red
					checkerImageData->at( index + 1 ) = static_cast< unsigned char >( 0 );		// green
					checkerImageData->at( index + 2 ) = static_cast< unsigned char >( c );		// blue
					checkerImageData->at( index + 3 ) = static_cast< unsigned char >( 255 );	// alpha
				}
			}

			return( std::make_shared< CImage >( size, size, true, 32, size.width * 4, std::move( checkerImageData ) ) );
		}
	}
}
