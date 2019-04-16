#pragma once

#include <unordered_map>

#include <AL/al.h>
#include <AL/alc.h>

#include <glm/glm.hpp>

#include "src/helper/Types.hpp"

#include "src/system/CSettings.hpp"

#include "src/resource/CResourceCacheManager.hpp"

#include "src/audio/CAudioBuffer.hpp"
#include "src/audio/CAudioBufferCache.hpp"

class CAudio final
{
friend class CEngine;
friend class CEngineInterface;

public:
	void	SetListener( const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &up );
	void	SetVolume( const f16 volume );

	class Exception: public std::exception
	{
	public:
		explicit Exception() {}

		virtual ~Exception() throw() {}
	};

private:
	CAudio( const CSettings &settings, const CFileSystem &p_filesystem, CResourceCacheManager &resourceCacheManager );
	~CAudio();

	CAudio( const CAudio &rhs ) = delete;
	CAudio& operator = ( const CAudio &rhs ) = delete;

private:
	ALCdevice	*m_AL_device { nullptr };
	ALCcontext	*m_AL_context { nullptr };

	// TODO what does this do???
	const u32	m_buffer_size;

	CResourceCacheManager &m_resourceCacheManager;

	std::shared_ptr< CAudioBufferCache > m_audioBufferCache;
};
