#include "Log.h"
#include <iostream>


Logger::Logger()
	: m_LogLevel(LogLevel::INFO) {}

void Logger::SetLogLevel(LogLevel level)
{
	m_LogLevel = level;
}

template<typename T>
void Logger::Info(T& log)
{
	if (m_LogLevel >= LogLevel::INFO)
		std::cout << "[INFO] - " << log << std::endl;
}

template<typename T>
void Logger::Warn(T& log)
{
	if (m_LogLevel >= LogLevel::WARN)
		std::cout << "[WARN] - " << log << std::endl;
}

template<typename T>
void Logger::Error(T& log)
{
	if (m_LogLevel >= LogLevel::ERROR)
		std::cout << "[ERROR] - " << log << std::endl;
}
