#include "Logger.h"
#include "Core/FileIO.h"
#include <iostream>

namespace jojo 
{
	Logger g_logger(LogLevel::Info, &std::cout);

	bool Logger::log(LogLevel logLevel, const std::string fileName, int line)
	{
		if (logLevel > m_logLevel) return false;

		switch (logLevel)
		{
		case LogLevel::Info:
			*m_ostream << "INFO: ";
			break;
		case LogLevel::Warning:
			*m_ostream << "WARNING: ";
			break;
		case LogLevel::Error:
			*m_ostream << "ERROR: ";
			break;
		case LogLevel::Assert:
			*m_ostream << "ASSERT: ";
			break;
		default:
			break;
		}

		*m_ostream << jojo::GetFileName(fileName) << "(" << line << ")\n";

		return true;
	}
}