#ifndef CSOUNDMANAGER_HPP
#define CSOUNDMANAGER_HPP

#include <unordered_map>

#include <AL/al.h>
#include <AL/alc.h>

#include <glm/glm.hpp>

#include "src/engine/system/CSettings.hpp"

#include "src/engine/resource/CResourceCacheManager.hpp"

#include "src/engine/sound/CSoundBuffer.hpp"
#include "src/engine/sound/CSoundBufferCache.hpp"

class CSoundManager final
{
friend class CEngine;
friend class CEngineInterface;

public:
	void	SetListener( const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &up );

	class Exception: public std::exception
	{
	public:
		explicit Exception( void ) {}

		virtual ~Exception() throw() {}
	};

private:
	CSoundManager( const CSettings &settings, const CFileSystem &p_filesystem, CResourceCacheManager &resourceCacheManager );
	~CSoundManager( void );

	CSoundManager( const CSoundManager &rhs ) = delete;
	CSoundManager& operator = ( const CSoundManager &rhs ) = delete;

private:
	ALCdevice	*m_AL_device { nullptr };
	ALCcontext	*m_AL_context { nullptr };

	// TODO what does this do???
	const std::uint32_t	m_buffer_size;

	CResourceCacheManager &m_resourceCacheManager;

	std::shared_ptr< CSoundBufferCache > m_soundBufferCache;
};

#endif // CSOUNDMANAGER_HPP
