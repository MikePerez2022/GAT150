#include "Logger.h"
#include "Core/FileIO.h"
#include <iostream>

namespace jojo 
{

	bool Logger::log(LogLevel logLevel, const std::string fileName, int line)
	{
		if (logLevel < m_logLevel) return false;

		switch (logLevel)
		{
		case LogLevel::Info:
			*this << "INFO: ";
			break;
		case LogLevel::Warning:
			*this << "WARNING: ";
			break;
		case LogLevel::Error:
			*this << "ERROR: ";
			break;
		case LogLevel::Assert:
			*this << "ASSERT: ";
			break;
		default:
			break;
		}

		*this << jojo::GetFileName(fileName) << "(" << line << ") ";

		return true;
	}
}