#ifndef CENGINEINTERFACE_HPP
#define CENGINEINTERFACE_HPP

#include "CInput.hpp"

#include "src/engine/sound/CSoundManager.hpp"

#include "src/engine/renderer/CRenderer.hpp"

#include "src/engine/resource/CResourceCacheManager.hpp"

class CEngineInterface final
{
public:
	CEngineInterface( const CSettings &settings, const CFileSystem &filesystem );
	~CEngineInterface();

	CResourceCacheManager ResourceCacheManager;

	CInput			Input;
	CRenderer		Renderer;
	CSoundManager	SoundManager;

private:
	CEngineInterface( const CEngineInterface &rhs ) = delete;
	CEngineInterface& operator = ( const CEngineInterface &rhs ) = delete;
};

#endif // CENGINEINTERFACE_HPP
