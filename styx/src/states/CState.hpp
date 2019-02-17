#pragma once

#include <memory>

#include "src/system/CEngineInterface.hpp"
#include "src/system/CTimer.hpp"

#include "src/renderer/CFrameBuffer.hpp"

#include "src/scene/CScene.hpp"

#include "src/system/CFileSystem.hpp"
#include "src/system/CSettings.hpp"

class CState : public std::enable_shared_from_this< CState >
{
private:
	CState( const CState &rhs ) = delete;
	CState& operator = ( const CState &rhs ) = delete;

protected:
	CState( const std::string &name, const CFileSystem &filesystem, const CSettings &settings, CEngineInterface &engineInterface );
	virtual ~CState() {};

public:
	[[nodiscard]] virtual std::shared_ptr< CState > Update() final;
	[[nodiscard]] virtual std::shared_ptr< CState > OnUpdate() = 0;

	virtual void Pause() final;
	virtual void OnPause() {};

	virtual void Resume() final;
	virtual void OnResume() {};

	[[nodiscard]] virtual const CScene &Scene() const final;

	[[nodiscard]] virtual const std::string &Name() const final;

	[[nodiscard]] virtual const CFrameBuffer &FrameBuffer() const final;

	[[nodiscard]] virtual const CTimer &Timer() const final;

protected:
	const std::string	m_name;

	const CFrameBuffer m_frameBuffer;

	const CFileSystem	&m_filesystem;
	const CSettings		&m_settings;

	CTimer m_timer;

	CScene m_scene;

	CEngineInterface &m_engineInterface;

private:
	enum class eStatus
	{
		RUNNING,
		PAUSED
	};

	eStatus m_status = eStatus::RUNNING;
};
