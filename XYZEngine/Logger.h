#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>

namespace XYZEngine
{
	enum class LogLevel
	{
		TRACE,
		INFO,
		WARNING,
		ERR,
		FATAL
	};

	class Logger
	{
	private:
		inline static std::ofstream fileStream;

	public:
		static void Init()
		{
			fileStream.open("game_log.txt", std::ios::out | std::ios::app);
			Log(LogLevel::INFO, "Logger initialized.");
		}

		static void Log(LogLevel level, const std::string& message)
		{
			std::string prefix;
			switch (level)
			{
			case LogLevel::TRACE:   prefix = "[TRACE] "; break;
			case LogLevel::INFO:    prefix = "[INFO] "; break;
			case LogLevel::WARNING: prefix = "[WARNING] "; break;
			case LogLevel::ERR:     prefix = "[ERROR] "; break;
			case LogLevel::FATAL:   prefix = "[FATAL] "; break;
			}
			
			std::string fullMessage = prefix + message;

			// Логирование в консоль
			(level >= LogLevel::ERR ? std::cerr : std::cout) << fullMessage << std::endl;

			// Логирование в файл
			if (fileStream.is_open())
			{
				fileStream << fullMessage << std::endl;
				fileStream.flush();
			}
		}
	};
}

#define XYZ_ASSERT(condition, message) \
	do { \
		if (!(condition)) { \
			XYZEngine::Logger::Log(XYZEngine::LogLevel::FATAL, std::string("Assertion failed: ") + message); \
			throw std::runtime_error(message); \
		} \
	} while(false)
