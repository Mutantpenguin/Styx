#include "CMesh.hpp"

#include <algorithm>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "src/engine/logger/CLogger.hpp"

CMesh::CMesh( GLenum Mode, const Primitives::SPrimitive &primitive, const std::shared_ptr< const CMaterial > &mat, const TMeshTextureSlots &textureSlots ) :
	m_vao( Mode, primitive ),
	m_material { mat },
	m_textureSlots { textureSlots },
	m_boundingSphereRadiusVector { CalculateBoundingSphereRadiusVector( primitive ) }
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

void CMesh::ChangeTexture( const std::string &slotName, const std::shared_ptr< const CTexture > &texture )
{
	const auto &meshTextureSlot = m_textureSlots.find( slotName );
	if( meshTextureSlot == std::cend( m_textureSlots ) )
	{
		logWARNING( "changing texture for slot {0} in mesh failed because it does not exist", slotName );
	}
	else
	{
		meshTextureSlot->second->m_texture = texture;
	}
}

void CMesh::ChangeSampler( const std::string &slotName, const std::shared_ptr< const CSampler > &sampler )
{
	const auto &meshTextureSlot = m_textureSlots.find( slotName );
	if( meshTextureSlot == std::cend( m_textureSlots ) )
	{
		logWARNING( "changing sampler for slot {0} in mesh failed because it does not exist", slotName );
	}
	else
	{
		meshTextureSlot->second->m_sampler = sampler;
	}
}

void CMesh::ChangeTextureAndSampler( const std::string &slotName, const std::shared_ptr< const CTexture > &texture, const std::shared_ptr< const CSampler > &sampler )
{
	const auto &meshTextureSlot = m_textureSlots.find( slotName );
	if( meshTextureSlot == std::cend( m_textureSlots ) )
	{
		logWARNING( "changing texture and sampler for slot {0} in mesh failed because it does not exist", slotName );
	}
	else
	{
		meshTextureSlot->second->m_texture	= texture;
		meshTextureSlot->second->m_sampler	= sampler;
	}
}

void CMesh::SetupMaterialTextureMapping( void )
{
	m_materialTextureSlotMapping.clear();

	if( m_material )
	{
		for( const auto & [ location, interface ] : m_material->Shader()->RequiredSamplers() )
		{
			if( const auto textureSlot = m_textureSlots.find( interface.name ); textureSlot != std::cend( m_textureSlots ) )
			{
				m_materialTextureSlotMapping.emplace_back( std::make_pair( location, textureSlot->second ) );
			}
			else
			{
				logWARNING( "setting up texture mapping for mesh failed because a slot with the name '{0}' does not exist in the mesh", interface.name );
			}
		}
	}
}

const std::shared_ptr< const CMaterial > &CMesh::Material( void ) const
{
	return( m_material );
}

const CVAO &CMesh::VAO( void ) const
{
	return( m_vao );
}

const glm::vec3 &CMesh::BoundingSphereRadiusVector( void ) const
{
	return( m_boundingSphereRadiusVector );
}

glm::vec3 CMesh::CalculateBoundingSphereRadiusVector( const Primitives::SPrimitive &primitive )
{
	return( (*std::max_element( std::cbegin( primitive.Vertices ), std::cend( primitive.Vertices ), []( const Primitives::SVertex &a, const Primitives::SVertex &b ){ return( glm::length2( a.Position ) > glm::length2( b.Position ) ); } ) ).Position );
}

void CMesh::BindTextures( void ) const
{
	std::uint8_t textureUnit = 0;
	for( const auto & [ location, meshTexture ] : m_materialTextureSlotMapping )
	{
		glUniform1i( location, textureUnit );

		meshTexture->BindToUnit( textureUnit );

		textureUnit++;
	}
}
