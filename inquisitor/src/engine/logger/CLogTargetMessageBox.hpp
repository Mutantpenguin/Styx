#ifndef CLOGTARGETMESSAGEBOX_HPP
#define CLOGTARGETMESSAGEBOX_HPP

#include "src/engine/logger/CLogger.hpp"

class CLogTargetMessageBox final : public CLogger::CLogTarget
{
	friend class CLogger;

public:
	explicit CLogTargetMessageBox( const CLogger::TLogBuffer & ) {};

private:
	virtual void Log( const std::unique_ptr< const CLogger::logEntry > &entry ) override;
};

#endif // CLOGTARGETMESSAGEBOX_HPP
