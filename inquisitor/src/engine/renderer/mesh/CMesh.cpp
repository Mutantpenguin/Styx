#include "CMesh.hpp"

#include <algorithm>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "src/engine/logger/CLogger.hpp"

CMesh::CMesh( GLenum Mode, const Primitives::SPrimitive &primitive, const std::shared_ptr< const CMaterial > &mat, const glm::vec3 &position, const glm::vec3 &orientation, const glm::vec3 &scale, const TTextures &textures ) :
	m_vao( Mode, primitive ),
	m_material { mat },
	m_textures { textures },
	m_position { position },
	m_orientation { orientation },
	m_scale { scale },
	m_boundingSphereRadiusVector { CalculatedBoundingSphereRadiusVector( primitive ) },
	m_boundingSphereRadius { CalculatedBoundingSphereRadius( m_boundingSphereRadiusVector, m_scale ) }
{
	CalculateModelMatrix();

	SetupMaterialTextureMapping();
}

CMesh::CMesh( GLenum Mode, const Primitives::SPrimitive &primitive, const std::shared_ptr< const CMaterial > &mat, const glm::vec3 &position, const glm::vec3 &orientation, const TTextures &textures ) :
	m_vao( Mode, primitive ),
	m_material { mat },
	m_textures { textures },
	m_position { position },
	m_orientation { orientation },
	m_boundingSphereRadiusVector { CalculatedBoundingSphereRadiusVector( primitive ) },
	m_boundingSphereRadius { CalculatedBoundingSphereRadius( m_boundingSphereRadiusVector, m_scale ) }
{
	CalculateModelMatrix();

	SetupMaterialTextureMapping();
}

CMesh::CMesh( GLenum Mode, const Primitives::SPrimitive &primitive, const std::shared_ptr< const CMaterial > &mat, const glm::vec3 &position, const TTextures &textures ) :
	m_vao( Mode, primitive ),
	m_material { mat },
	m_textures { textures },
	m_position { position },
	m_boundingSphereRadiusVector { CalculatedBoundingSphereRadiusVector( primitive ) },
	m_boundingSphereRadius { CalculatedBoundingSphereRadius( m_boundingSphereRadiusVector, m_scale ) }
{
	CalculateModelMatrix();

	SetupMaterialTextureMapping();
}

CMesh::CMesh( GLenum Mode, const Primitives::SPrimitive &primitive, const std::shared_ptr< const CMaterial > &mat, const TTextures &textures ) :
	m_vao( Mode, primitive ),
	m_material { mat },
	m_textures { textures },
	m_materialTextureMapping( m_textures.size() ),
	m_boundingSphereRadiusVector { CalculatedBoundingSphereRadiusVector( primitive ) },
	m_boundingSphereRadius { CalculatedBoundingSphereRadius( m_boundingSphereRadiusVector, m_scale ) }
{
	CalculateModelMatrix();

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
							if( texture->Type() != CTexture::type::TEX_2D )
							{
								logWARNING( "required texture for sampler '{0}' has to be of type 2D in '{1}'", interface.name, path );
								return( false );
							}
							break;

						case GL_SAMPLER_CUBE:
							if( texture->Type() != CTexture::type::TEX_CUBE_MAP )
							{
								logWARNING( "required texture for sampler '{0}' has to be of type CUBEMAP in '{1}'", interface.name, path );
								return( false );
							}
							break;

						case GL_SAMPLER_2D_ARRAY:
							if( texture->Type() != CTexture::type::TEX_2D_ARRAY )
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
						case CTexture::type::TEX_2D:
							sampler = m_samplerManager.SamplerFromType( CSampler::Type::REPEAT_2D );
							break;

						case CTexture::type::TEX_CUBE_MAP:
							sampler = m_samplerManager.SamplerFromType( CSampler::Type::REPEAT_CUBE );
							break;

						case CTexture::type::TEX_2D_ARRAY:
							sampler = m_samplerManager.SamplerFromType( CSampler::Type::REPEAT_2D );
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
	const auto meshTexture = m_textures.find( name );
	if( meshTexture == std::cend( m_textures ) )
	{
		logWARNING( "changing texture {0} in mesh failed because it does not exist in the mesh", name );
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

	for( const auto & [ location, interface ] : m_material->Shader()->RequiredSamplers() )
	{
		if( const auto texture = m_textures.find( interface.name ); texture != std::cend( m_textures ) )
		{
			m_materialTextureMapping.emplace_back( std::make_pair( location, texture->second ) );
		}
		else
		{
			logWARNING( "setting up texture mapping for mesh failed because texture '{0}' does not exist in the mesh", interface.name );
		}
	}
}

const std::shared_ptr< const CMaterial > &CMesh::Material( void ) const
{
	return( m_material );
}

void CMesh::SetScale( const glm::vec3 &scale )
{
	m_scale = scale;
	m_boundingSphereRadius = CalculatedBoundingSphereRadius( m_boundingSphereRadiusVector, m_scale );
	CalculateModelMatrix();
}

const glm::vec3 &CMesh::Scale( void ) const
{
	return( m_scale );
}

void CMesh::SetPosition( const glm::vec3 &position )
{
	m_position = position;
	CalculateModelMatrix();
}

const glm::vec3 &CMesh::Position( void ) const
{
	return( m_position );
}

void CMesh::SetOrientation( const glm::vec3 &orientation )
{
	m_orientation = orientation;
	CalculateModelMatrix();
}

const glm::vec3 &CMesh::Orientation( void ) const
{
	return( m_orientation );
}

const CVAO &CMesh::VAO( void ) const
{
	return( m_vao );
}

float CMesh::BoundingSphereRadius( void ) const
{
	return( m_boundingSphereRadius );
}

const glm::mat4 &CMesh::ModelMatrix( void ) const
{
	return( m_modelMatrix );
}

void CMesh::CalculateModelMatrix( void )
{
	m_modelMatrix = glm::mat4();

	m_modelMatrix = glm::translate( m_modelMatrix, m_position );

	const glm::vec3 rotationRadians = glm::vec3( glm::radians( m_orientation.x ), glm::radians( m_orientation.y ), glm::radians( m_orientation.z ) );
	m_modelMatrix = m_modelMatrix * glm::toMat4( glm::quat( rotationRadians ) );

	m_modelMatrix = glm::scale( m_modelMatrix, m_scale );
}

glm::vec3 CMesh::CalculatedBoundingSphereRadiusVector( const Primitives::SPrimitive &primitive )
{
	return( *std::max_element( std::cbegin( primitive.vertices ), std::cend( primitive.vertices ), []( glm::vec3 a, glm::vec3 b ){ return( glm::length2( a ) > glm::length2( b ) ); } ) );
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
