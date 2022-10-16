#pragma once

enum LogLevel
{
	INFO=0, WARN=1, ERROR=2
};


class Logger
{
private:
	LogLevel m_LogLevel;
public:
	Logger();

	void SetLogLevel(LogLevel level);

	template<typename T>
	void Info(T& log);

	template<typename T>
	void Warn(T& log);

	template<typename T>
	void Error(T& log);
};
