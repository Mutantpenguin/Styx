#ifndef CSTATEPAUSE_HPP
#define CSTATEPAUSE_HPP

#include "CState.hpp"

class CStatePause : public CState
{
public:
	CStatePause( const CFileSystem &filesystem, const CSettings &settings, CRenderer &renderer, std::shared_ptr< CState > state );
	~CStatePause();

	virtual void Render( const CRenderer &renderer, const std::uint64_t time ) const override;

	virtual std::shared_ptr< CState > Update( const std::uint64_t time, CSoundManager &soundManager, CRenderer &renderer, const CInput &input ) override;

private:
	const std::shared_ptr< CState > m_state;
};

#endif // CSTATEPAUSE_HPP
