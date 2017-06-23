#ifndef CSTATEPAUSE_HPP
#define CSTATEPAUSE_HPP

#include "CState.hpp"

class CStatePause : public CState
{
private:
	CStatePause( const CStatePause& rhs );
	CStatePause& operator=( const CStatePause& rhs );

public:
	CStatePause( const CFileSystem &filesystem, const CSettings &settings, CEngineSystems &engineSystems, std::shared_ptr< CState > pausedState );
	~CStatePause();

	virtual std::shared_ptr< CState > Update( void ) override;

private:
	const std::uint64_t m_startTime;

	const std::shared_ptr< CState > m_pausedState;

	std::shared_ptr< CMesh > m_meshText;
	std::shared_ptr< CMesh > m_screenshotMesh;
};

#endif // CSTATEPAUSE_HPP
