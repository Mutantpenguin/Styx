#include "CMaterialLayer.hpp"

#include "src/engine/renderer/CGLState.hpp"

#include "src/engine/logger/CLogger.hpp"

void CMaterialLayer::Update( const float delta )
{
    m_textureMatrix = glm::mat3();

    for( auto mod : m_texcoordmods )
    {
        m_textureMatrix = mod->Update( delta ) * m_textureMatrix;
    }
}
