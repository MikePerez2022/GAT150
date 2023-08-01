#pragma once
#include <string>
#include <cassert>
#include <fstream>

#define INFO_LOG { jojo::g_logger.log(jojo::LogLevel::Info, __FILE__, __LINE__); }
#define WARNING_LOG { jojo::g_logger.log(jojo::LogLevel::Warning, __FILE__, __LINE__); }
#define ERROR_LOG { jojo::g_logger.log(jojo::LogLevel::Error, __FILE__, __LINE__); }
#define ASSERT_LOG { jojo::g_logger.log(jojo::LogLevel::Assert, __FILE__, __LINE__); }


namespace jojo
{
	enum class LogLevel
	{
		Info,
		Warning,
		Error,
		Assert
	};

	class Logger
	{
	public:
		Logger(LogLevel logLevel, std::ostream* ostream) : 
			m_logLevel{ logLevel }, 
			m_ostream{ ostream } 
		{}

		bool log(LogLevel logLevel, const std::string fileName, int line);

	private:
		LogLevel m_logLevel = jojo::LogLevel::Info;

		std::ostream* m_ostream = nullptr;
		std::ofstream m_fstream;
	};

	extern Logger g_logger;
}