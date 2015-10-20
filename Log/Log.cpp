
#include "Log.h"
#include <cstdio>
#include <ctime>
#include <Windows.h>
#include <direct.h>
#include <fstream>

Log* Log::GetInstance()
{
	static Log log;
	return &log;
}

void Log::Print(const char* File, const char* Function, int LineNumber, const char* LogCategory, Verbosity::Type VerbosityLevel, OutputMethod::Type OutMethod, DetailLevel::Type Detail, const char* Format, ...)
{
	if (OutMethod == OutputMethod::ConsoleWindow || OutMethod == OutputMethod::All)
	{
		SetTextColorToVerbosityLevel(VerbosityLevel);

		if (Detail == DetailLevel::High)
		{
			PrintTimeStamp();
			printf("[File: %s, Function: %s, Line: %d] - ", File, Function, LineNumber);
		}
		else if (Detail == DetailLevel::Medium)
		{
			printf("[File: %s, Function: %s, Line: %d] - ", File, Function, LineNumber);
		}

		va_list ap;
		va_start(ap, Format);
		vprintf(Format, ap);
		va_end(ap);
		printf("\n");
	}

	if (OutMethod == OutputMethod::OutputWindow || OutMethod == OutputMethod::All)
	{
		//if (Detail == DetailLevel::High)
		//{
		//	OutputTimeStamp();
		//	
		//	char buffer[256];
		//	va_list args;
		//	va_start(args, buffer);
		//	
		//	//vsnprintf_s(buffer, _countof(buffer), _TRUNCATE, Format, args);
		//	va_end(args);
		//	printf(buffer);
		//}
		//else if (Detail == DetailLevel::Medium)
		//{
		//	
		//}
		//else
		//{
		//	// Do nothing extra for low detail.
		//}
	}
	
	if (OutMethod == OutputMethod::TextFile || OutMethod == OutputMethod::All)
	{
		// If an OutputLogs folder does not exist, create one.
		DWORD filetype = GetFileAttributes(L"OutputLogs");
		if (filetype == INVALID_FILE_ATTRIBUTES && (filetype & FILE_ATTRIBUTE_DIRECTORY))
		{
			_mkdir("OutputLogs");
		}

		std::string filename = "OutputLogs/";
		filename += LogCategory;
		filename += ".txt";
		
		char streamBuffer[512];
		va_list args;
		va_start(args, Format);
		vsnprintf_s(streamBuffer, _countof(streamBuffer), _TRUNCATE, Format, args);
		va_end(args);

		std::ofstream fout;
		fout.open(filename.c_str(), std::ios_base::out | std::ios_base::app);
		if (fout.is_open())
		{
			if (Detail == DetailLevel::High)
			{
				time_t now = time(0);
				tm timeInfo;
				localtime_s(&timeInfo, &now);
				char timeStampBuffer[36];
				sprintf_s(timeStampBuffer,"[%d.%02d.%02d-%02d:%02d:%02d] ", timeInfo.tm_year + 1900, timeInfo.tm_mon + 1, timeInfo.tm_mday, timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
				fout << timeStampBuffer;
				char detailBuffer[64];
				sprintf_s(detailBuffer, "[File: %s, Function: %s, Line: %d] - ", File, Function, LineNumber);
				fout << detailBuffer;
			}
			else if (Detail == DetailLevel::Medium)
			{
				char detailBuffer[64];
				sprintf_s(detailBuffer, "[File: %s, Function: %s, Line: %d] - ", File, Function, LineNumber);
				fout << detailBuffer;
			}

			if (VerbosityLevel == Verbosity::Default)
			{
				fout << "DEFAULT: ";
			}
			else if (VerbosityLevel == Verbosity::Debug)
			{
				fout << "DEBUG: ";
			}
			else if (VerbosityLevel == Verbosity::Warning)
			{
				fout << "WARNING: ";
			}
			else if (VerbosityLevel == Verbosity::Error)
			{
				fout << "ERROR: ";
			}

			fout << streamBuffer << std::endl;
			fout.close();
		}
	}
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
