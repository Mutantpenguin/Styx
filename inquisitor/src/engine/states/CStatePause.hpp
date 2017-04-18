#ifndef CSTATEPAUSE_HPP
#define CSTATEPAUSE_HPP

#include "CState.hpp"

class CStatePause : public CState
{
public:
	CStatePause( const CFileSystem &filesystem, const CSettings &settings, CEngineSystems &engineSystems, std::shared_ptr< CState > state );
	~CStatePause();

	virtual void Render( void ) const override;

	virtual std::shared_ptr< CState > Update( void ) override;

private:
	const std::shared_ptr< CState > m_state;
};

#endif // CSTATEPAUSE_HPP
