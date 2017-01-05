#ifndef CLOGTARGETCONSOLE_HPP
#define CLOGTARGETCONSOLE_HPP

#include "src/engine/logger/CLogger.hpp"

class CLogTargetConsole final : public CLogger::CLogTarget
{
	friend class CLogger;

public:
	CLogTargetConsole( const CLogger::TLogBuffer & ) {};

private:
	virtual void Log( const std::unique_ptr< const CLogger::logEntry > &entry ) override;

#ifndef WIN32
	std::string	GetColor( e_loglevel level ) const;
	void		SetColor( const std::string &color ) const;
#else
	int		GetColor( e_loglevel level ) const;
	void	SetColor( const int &color ) const;
#endif
};

#endif // CLOGTARGETCONSOLE_HPP
