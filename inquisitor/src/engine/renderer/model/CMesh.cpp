#include "CMesh.hpp"

#include <algorithm>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "src/engine/logger/CLogger.hpp"

CMesh::CMesh( GLenum Mode, const Primitives::SPrimitive &primitive, const std::shared_ptr< const CMaterial > &mat, const glm::vec3 &scale, const TTextures &textures ) :
	m_vao( Mode, primitive ),
	m_material { mat },
	m_textures { textures },
	m_scale { scale },
	m_boundingSphereRadiusVector { CalculatedBoundingSphereRadiusVector( primitive ) },
	m_boundingSphereRadius { CalculatedBoundingSphereRadius( m_boundingSphereRadiusVector, m_scale ) }
{
	SetupMaterialTextureMapping();
}

CMesh::CMesh( GLenum Mode, const Primitives::SPrimitive &primitive, const std::shared_ptr< const CMaterial > &mat, const TTextures &textures ) :
	m_vao( Mode, primitive ),
	m_material { mat },
	m_textures { textures },
	m_boundingSphereRadiusVector { CalculatedBoundingSphereRadiusVector( primitive ) },
	m_boundingSphereRadius { CalculatedBoundingSphereRadius( m_boundingSphereRadiusVector, m_scale ) }
{
	SetupMaterialTextureMapping();
}

void CMesh::SetMaterial( const std::shared_ptr< const CMaterial > &mat )
{
	m_material = mat;

	SetupMaterialTextureMapping();

	/* TODO setup the necessary things for the material
	 * const auto mat_texture = mat_textures->find( interface.name );
				if( mat_texture == mat_textures->cend() )
				{
					logWARNING( "required texture for sampler '{0}' not specified in '{1}'", interface.name, path );
					return( false );
				}
				else
				{
					// check that sampler-type and type of texture match

					const std::shared_ptr< const CTexture > texture = m_textureManager.LoadTexture( mat_texture->get<std::string>() );

					switch( interface.type )
					{
						case GL_SAMPLER_2D:
							if( texture->Type() != CTexture::TextureType::TEX_2D )
							{
								logWARNING( "required texture for sampler '{0}' has to be of type 2D in '{1}'", interface.name, path );
								return( false );
							}
							break;

						case GL_SAMPLER_CUBE:
							if( texture->Type() != CTexture::TextureType::TEX_CUBE_MAP )
							{
								logWARNING( "required texture for sampler '{0}' has to be of type CUBEMAP in '{1}'", interface.name, path );
								return( false );
							}
							break;

						case GL_SAMPLER_2D_ARRAY:
							if( texture->Type() != CTexture::TextureType::TEX_2D_ARRAY )
							{
								logWARNING( "required texture for sampler '{0}' has to be of type 2D_ARRAY in '{1}'", interface.name, path );
								return( false );
							}
							break;

						default:
							logERROR( "unhandled type '{0}' for sampler '{1}'", glbinding::Meta::getString( interface.type ), interface.name );
							return( false );
					}

----------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------


const auto mat_samplers = mat_root.find( "samplers" );

		if( !shader->RequiredSamplers().empty() )
		{
			for( const auto & [ location, interface ] : shader->RequiredSamplers() )
			{
				std::shared_ptr< const CSampler > sampler;

				if( mat_samplers != mat_root.cend() )
				{
					const auto mat_sampler = mat_samplers->find( interface.name );
					if( ( mat_sampler != mat_samplers->cend() ) && ( !mat_sampler->empty() ) )
					{
						// TODO check here, if specified sampler fits to the sampelr in the shader
						if( !m_samplerManager.SamplerFromString( mat_sampler->get<std::string>(), sampler ) )
						{
							logDEBUG( "invalid sampler specified for sampler '{0}' in '{1}'", interface.name, path );
						}
					}
				}

				// TODO set default samplers where not already set
				if( !sampler )
				{
					// TODO by type of sampler
					switch( texture->Type() )
					{
						case CTexture::TextureType::TEX_2D:
							sampler = m_samplerManager.SamplerFromSamplerType( CSampler::SamplerType::REPEAT_2D );
							break;

						case CTexture::TextureType::TEX_CUBE_MAP:
							sampler = m_samplerManager.SamplerFromSamplerType( CSampler::SamplerType::REPEAT_CUBE );
							break;

						case CTexture::TextureType::TEX_2D_ARRAY:
							sampler = m_samplerManager.SamplerFromSamplerType( CSampler::SamplerType::REPEAT_2D );
							break;

						default:
							logWARNING( "unknown type for sampler specified for texture '{0}' in '{1}'", interface.name, path );
							return( false );
					}
				}

				mat->m_samplerData.insert( std::make_pair( location, CMaterialSamplerData( interface.name, sampler ) ) );
			}
		}
 * */
}

void CMesh::ChangeTexture( const std::string &name, const std::shared_ptr< const CTexture > &texture, const std::shared_ptr< const CSampler > &sampler )
{
	const auto &meshTexture = m_textures.find( name );
	if( meshTexture == std::cend( m_textures ) )
	{
		logWARNING( "changing texture with the name {0} in mesh failed because it does not exist", name );
	}
	else
	{
		meshTexture->second->m_texture	= texture;
		meshTexture->second->m_sampler	= sampler;
	}
}

void CMesh::SetupMaterialTextureMapping( void )
{
	m_materialTextureMapping.clear();

	if( m_material )
	{
		for( const auto & [ location, interface ] : m_material->Shader()->RequiredSamplers() )
		{
			if( const auto texture = m_textures.find( interface.name ); texture != std::cend( m_textures ) )
			{
				m_materialTextureMapping.emplace_back( std::make_pair( location, texture->second ) );
			}
			else
			{
				logWARNING( "setting up texture mapping for mesh failed because a texture with name '{0}' does not exist in the mesh", interface.name );
			}
		}
	}
}

const std::shared_ptr< const CMaterial > &CMesh::Material( void ) const
{
	return( m_material );
}

void CMesh::Scale( const glm::vec3 &scale )
{
	m_scale = scale;
	m_boundingSphereRadius = CalculatedBoundingSphereRadius( m_boundingSphereRadiusVector, m_scale );
}

const glm::vec3 &CMesh::Scale( void ) const
{
	return( m_scale );
}

const CVAO &CMesh::VAO( void ) const
{
	return( m_vao );
}

float CMesh::BoundingSphereRadius( void ) const
{
	return( m_boundingSphereRadius );
}

glm::vec3 CMesh::CalculatedBoundingSphereRadiusVector( const Primitives::SPrimitive &primitive )
{
	return( (*std::max_element( std::cbegin( primitive.Vertices ), std::cend( primitive.Vertices ), []( const Primitives::SVertex &a, const Primitives::SVertex &b ){ return( glm::length2( a.Position ) > glm::length2( b.Position ) ); } ) ).Position );
}

float CMesh::CalculatedBoundingSphereRadius( const glm::vec3 &radiusVector, const glm::vec3 &scale )
{
	return( glm::length( radiusVector * scale ) );
}

void CMesh::BindTextures( void ) const
{
	std::uint8_t textureUnit = 0;
	for( const auto & [ location, meshTexture ] : m_materialTextureMapping )
	{
		glUniform1i( location, textureUnit );

		meshTexture->BindToUnit( textureUnit );

		textureUnit++;
	}
}
