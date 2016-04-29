#include "CMaterialLayer.hpp"

#include "../CGLState.hpp"

#include "../../logger/CLogger.hpp"

void CMaterialLayer::Update( const float delta )
{
	/* TODO shaders
	if( ( m_textures.size() > 1 ) && ( m_animtime < timer.Time() ) )
	{
		if( m_textures.size() == m_current_texture )
		{
			m_current_texture = 1;
		}
		else
		{
			++m_current_texture;
		}
		m_animtime = timer.Time() + m_animFreq;
	}
	 * */

    m_textureMatrix = glm::mat3();

    for( auto mod : m_texcoordmods )
    {
        m_textureMatrix = mod->Update( delta ) * m_textureMatrix;
    }
}
