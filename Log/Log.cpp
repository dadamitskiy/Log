
#include "Log.h"
#include <cstdio>
#include <ctime>
#include <Windows.h>

Log* Log::GetInstance()
{
	static Log log;
	return &log;
}

void Log::Print(std::string szMessage)
{
	printf(szMessage.c_str());
}

void Log::Print(const char* Format, ...)
{
	va_list ap;
	va_start(ap, Format);
	vprintf(Format, ap);
	va_end(ap);
	printf("\n");
}

void Log::PrintTimeStamp()
{
	time_t now = time(0);
	tm timeInfo;
	localtime_s(&timeInfo, &now);
	
	printf("[%d.%02d.%02d-%02d:%02d:%02d] ", timeInfo.tm_year + 1900, timeInfo.tm_mon + 1, timeInfo.tm_mday, timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
}

void Log::OutputTimeStamp()
{
	time_t now = time(0);
	tm timeInfo;
	localtime_s(&timeInfo, &now);

	char szBuffer[23];
	sprintf_s(szBuffer, "[%d.%02d.%02d-%02d:%02d:%02d] ", timeInfo.tm_year + 1900, timeInfo.tm_mon + 1, timeInfo.tm_mday, timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);

#if UNICODE
	size_t convertedChars = 0;
	wchar_t wc[23];
	mbstowcs_s(&convertedChars, wc, szBuffer, _TRUNCATE);
	OutputDebugStringW(wc);
#else
	// @TODO
#endif
}

void Log::SetTextColorToVerbosityLevel(Verbosity::Type InLevel)
{
	switch (InLevel)
	{
	case Verbosity::Debug:
		// Set the color to green.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		break;
	case Verbosity::Warning:
		// Set the color to yellow.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		break;
	case Verbosity::Error:
		// Set the color to red.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		break;
	case Verbosity::Default:
		// Intended fallthrough.
	default:
		// Default it to a white color.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		break;
	}
}

void Log::ResetTextColor()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}
