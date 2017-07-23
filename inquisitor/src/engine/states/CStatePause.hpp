#ifndef CSTATEPAUSE_HPP
#define CSTATEPAUSE_HPP

#include "CState.hpp"

class CStatePause : public CState
{
private:
	CStatePause( const CStatePause& rhs );
	CStatePause& operator=( const CStatePause& rhs );

public:
	CStatePause( const CFileSystem &filesystem, const CSettings &settings, CEngineInterface &engineInterface, std::shared_ptr< CState > pausedState );
	~CStatePause();

	virtual std::shared_ptr< CState > Update( void ) override;

private:
	const std::uint64_t m_startTime;

	const std::shared_ptr< CState > m_pausedState;

	std::shared_ptr< CEntity > m_textEntity;
	std::shared_ptr< CEntity > m_screenshotEntity;
};

#endif // CSTATEPAUSE_HPP
