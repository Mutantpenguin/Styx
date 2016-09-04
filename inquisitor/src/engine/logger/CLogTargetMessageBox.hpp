#ifndef CLOGTARGETMESSAGEBOX_HPP
#define CLOGTARGETMESSAGEBOX_HPP

#include "CLogger.hpp"

class CLogTargetMessageBox final : public CLogger::CLogTarget
{
	friend class CLogger;

public:
	CLogTargetMessageBox( const CLogger::TLogBuffer & ) {};

private:
	virtual void Log( const std::unique_ptr< CLogger::logEntry > &entry ) override;
};

#endif // CLOGTARGETMESSAGEBOX_HPP
