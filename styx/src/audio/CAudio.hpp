#pragma once

#include <unordered_map>

#include <AL/al.h>
#include <AL/alc.h>

#include <glm/glm.hpp>

#include "src/core/Types.hpp"

#include "src/system/CSettings.hpp"

#include "src/resource/CResources.hpp"

#include "src/audio/CAudioBuffer.hpp"
#include "src/audio/CAudioBufferCache.hpp"

class CAudio final
{
friend class CEngine;
friend class CEngineInterface;

public:
	void	SetListener( const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &up );
	void	SetVolume( const f16 volume );

private:
	CAudio( const CSettings &settings, const CFileSystem &p_filesystem, CResources &resources );
	~CAudio();

	CAudio( const CAudio &rhs ) = delete;
	CAudio& operator = ( const CAudio &rhs ) = delete;

private:
	ALCdevice	*m_AL_device { nullptr };
	ALCcontext	*m_AL_context { nullptr };

	// TODO what does this do???
	const u32	m_buffer_size;

	CResources &m_resources;

	std::shared_ptr< CAudioBufferCache > m_audioBufferCache;
};
