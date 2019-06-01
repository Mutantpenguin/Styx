#include "CMesh.hpp"

#include <glbinding-aux/Meta.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "src/logger/CLogger.hpp"

void CMesh::SetMaterial( const std::shared_ptr<const CMaterial> &mat )
{
	m_material = mat;

	SetupMaterialTextureSlotMapping();

	/* TODO setup the necessary things for the material

		for( const auto & [ location, interface ] : shader->RequiredSamplers() )
		{
			std::shared_ptr<const CSampler> sampler;

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
		}
 * */
}

void CMesh::ChangeTexture( const std::string &slotName, const std::shared_ptr<const CTexture> &texture )
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

void CMesh::ChangeSampler( const std::string &slotName, const std::shared_ptr<const CSampler> &sampler )
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

void CMesh::ChangeTextureAndSampler( const std::string &slotName, const std::shared_ptr<const CTexture> &texture, const std::shared_ptr<const CSampler> &sampler )
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

void CMesh::SetupMaterialTextureSlotMapping()
{
	m_materialTextureSlotMapping.clear();

	if( m_material )
	{
		for( const auto & [ location, interface ] : m_material->ShaderProgram()->RequiredSamplers() )
		{
			if( const auto textureSlot = m_textureSlots.find( interface.name ); textureSlot != std::cend( m_textureSlots ) )
			{
				if( const auto texture = textureSlot->second->m_texture; nullptr != texture )
				{
					switch( interface.type )
					{
						case GL_SAMPLER_2D:
							if( texture->Type() != CTexture::EType::TEX_2D )
							{
								logWARNING( "setting up texture mapping for mesh failed because the texture for slot '{0}' has to be of type 2D", interface.name );
								continue;
							}
							break;

						case GL_SAMPLER_CUBE:
							if( texture->Type() != CTexture::EType::TEX_CUBE_MAP )
							{
								logWARNING( "setting up texture mapping for mesh failed because the texture for slot '{0}' has to be of type CUBEMAP", interface.name );
								continue;
							}
							break;

						case GL_SAMPLER_2D_ARRAY:
							if( texture->Type() != CTexture::EType::TEX_2D_ARRAY )
							{
								logWARNING( "setting up texture mapping for mesh failed because the texture for slot '{0}' has to be of type 2D_ARRAY", interface.name );
								continue;
							}
							break;

						default:
							logERROR( "unhandled type '{0}' for slot '{1}'", glbinding::aux::Meta::getString( interface.type ), interface.name );
							continue;
					}
				}

				m_materialTextureSlotMapping.emplace_back( std::make_pair( location, textureSlot->second ) );
			}
			else
			{
				logWARNING( "setting up texture mapping for mesh failed because a texture with the name '{0}' does not exist in the mesh", interface.name );
			}
		}
	}
}

const std::shared_ptr<const CMaterial> &CMesh::Material() const
{
	return( m_material );
}

void CMesh::Bind() const
{
	u8 textureUnit = 0;
	for( const auto & [ location, meshTextureSlot ] : m_materialTextureSlotMapping )
	{
		glUniform1i( location, textureUnit );

		meshTextureSlot->BindToUnit( textureUnit );

		textureUnit++;
	}

	m_vao.Bind();
}

void CMesh::Draw() const
{
	m_vao.Draw();
}