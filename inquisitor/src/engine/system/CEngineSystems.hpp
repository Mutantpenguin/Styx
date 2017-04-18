#ifndef CENGINESYSTEMS_HPP
#define CENGINESYSTEMS_HPP

#include "CInput.hpp"
#include "CTimer.hpp"

#include "src/engine/sound/CSoundManager.hpp"

#include "src/engine/renderer/CRenderer.hpp"

class CEngineSystems
{
public:
	CEngineSystems( const CSettings &settings, const CFileSystem &filesystem );
	~CEngineSystems();

	CInput			Input;
	CRenderer		Renderer;
	CSoundManager	SoundManager;
	CTimer			GlobalTimer;

private:
	CEngineSystems( const CEngineSystems &rhs ) = delete;
	CEngineSystems& operator = ( const CEngineSystems &rhs ) = delete;
};

#endif // CENGINESYSTEMS_HPP
