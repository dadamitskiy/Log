/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015-2016 Daniel Adamitskiy
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "Log.h"
#include <ctime>
#include <direct.h>
#include <Windows.h>

void Log::Print(const char* File, const char* Function, int LineNumber, const char* LogCategory, Verbosity::Type VerbosityLevel, OutputMethod::Type OutMethod, DetailLevel::Type Detail, const char* Format, ...)
{
	if (OutMethod == OutputMethod::ConsoleWindow || OutMethod == OutputMethod::All)
	{
		SetTextColorToVerbosityLevel(VerbosityLevel);

		if (Detail == DetailLevel::High)
		{
			PrintTimeStampToConsoleWindow();

			// Print the file, function, and line the LOG statement was called on.
			printf("[File: %s, Function: %s, Line: %d] - ", File, Function, LineNumber);
		}
		else if (Detail == DetailLevel::Medium)
		{
			// Print the file, function, and line the LOG statement was called on.
			printf("[File: %s, Function: %s, Line: %d] - ", File, Function, LineNumber);
		}

		// Print out the category.
		printf("Log%s ", LogCategory);

		// Print out the log calls verbosity level.
		if (VerbosityLevel == Verbosity::Default)
		{
			printf("DEFAULT: ");
		}
		else if (VerbosityLevel == Verbosity::Debug)
		{
			printf("DEBUG: ");
		}
		else if (VerbosityLevel == Verbosity::Warning)
		{
			printf("WARNING: ");
		}
		else if (VerbosityLevel == Verbosity::Error)
		{
			printf("ERROR: ");
		}
		else if (VerbosityLevel == Verbosity::Fatal)
		{
			printf("FATAL: ");
		}

		// Print out the LOG message.
		va_list ap;
		va_start(ap, Format);
		vprintf(Format, ap);
		va_end(ap);
		printf("\n");
	}

	if (OutMethod == OutputMethod::OutputWindow || OutMethod == OutputMethod::All)
	{
		// Ensure we are using Visual Studio to compile the code if we intend to log to its output window.
#if defined(_MSC_VER)
		if (Detail == DetailLevel::High)
		{
			PrintTimeStampToOutputWindow();

			// Output the file, function, and line the LOG statement was called on.
			char detailBuffer[128];
			sprintf_s(detailBuffer, "[File: %s, Function: %s, Line: %d] - ", File, Function, LineNumber);
			wchar_t wc[128];
			mbstowcs_s(nullptr, wc, detailBuffer, _TRUNCATE);
			OutputDebugStringW(wc);
		}
		else if (Detail == DetailLevel::Medium)
		{
			// Output the file, function, and line the LOG statement was called on.
			char detailBuffer[128];
			sprintf_s(detailBuffer, "[File: %s, Function: %s, Line: %d] - ", File, Function, LineNumber);
			wchar_t wc[128];
			mbstowcs_s(nullptr, wc, detailBuffer, _TRUNCATE);
			OutputDebugStringW(wc);
		}

		// Output the log category.
		char outputCategory[64];
		sprintf_s(outputCategory, "Log%s ", LogCategory);
		wchar_t wOutputCategory[64];
		mbstowcs_s(nullptr, wOutputCategory, outputCategory, _TRUNCATE);
		OutputDebugStringW(wOutputCategory);

		// Output the verbosity level.
		if (VerbosityLevel == Verbosity::Default)
		{
			OutputDebugStringW(L"DEFAULT: ");
		}
		else if (VerbosityLevel == Verbosity::Debug)
		{
			OutputDebugStringW(L"DEBUG: ");
		}
		else if (VerbosityLevel == Verbosity::Warning)
		{
			OutputDebugStringW(L"WARNING: ");
		}
		else if (VerbosityLevel == Verbosity::Error)
		{
			OutputDebugStringW(L"ERROR: ");
		}
		else if (VerbosityLevel == Verbosity::Fatal)
		{
			OutputDebugStringW(L"FATAL: ");
		}

		// Store the LOG message into the streamBuffer array.
		char streamBuffer[512];
		va_list args;
		va_start(args, Format);
		vsnprintf_s(streamBuffer, _countof(streamBuffer), _TRUNCATE, Format, args);
		va_end(args);

		// Output the LOG message to the output window.
		wchar_t wc[512];
		mbstowcs_s(nullptr, wc, streamBuffer, _TRUNCATE);
		OutputDebugStringW(wc);
		OutputDebugStringW(L"\n");
#endif
	}
	
	if (OutMethod == OutputMethod::TextFile || OutMethod == OutputMethod::All)
	{
		// If an OutputLogs folder does not exist, create one.
		DWORD filetype = GetFileAttributes(L"OutputLogs");
		if (filetype == INVALID_FILE_ATTRIBUTES && (filetype & FILE_ATTRIBUTE_DIRECTORY))
		{
			_mkdir("OutputLogs");
		}

		// Setup the text file name and path based off of the category name.
		std::string filename = "OutputLogs/";
		filename += LogCategory;
		filename += ".txt";
		
		// Store the LOG message into streamBuffer.
		char streamBuffer[512];
		va_list args;
		va_start(args, Format);
		vsnprintf_s(streamBuffer, _countof(streamBuffer), _TRUNCATE, Format, args);
		va_end(args);

		// Append the data to a text file.
		std::ofstream fout;
		fout.open(filename.c_str(), std::ios_base::out | std::ios_base::app);
		if (fout.is_open())
		{
			if (Detail == DetailLevel::High)
			{
				PrintTimeStampToTextFile(fout);
				
				// Print the file, function, and line the LOG statement was called on.
				char detailBuffer[128];
				sprintf_s(detailBuffer, "[File: %s, Function: %s, Line: %d] - ", File, Function, LineNumber);
				fout << detailBuffer;
			}
			else if (Detail == DetailLevel::Medium)
			{
				// Print the file, function, and line the LOG statement was called on.
				char detailBuffer[128];
				sprintf_s(detailBuffer, "[File: %s, Function: %s, Line: %d] - ", File, Function, LineNumber);
				fout << detailBuffer;
			}

			// Print out the verbosity level.
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
			else if (VerbosityLevel == Verbosity::Fatal)
			{
				fout << "FATAL: ";
			}

			fout << streamBuffer << std::endl;
			fout.close();
		}
	}

	// After we're done logging information, ensure fatal errors are caught.
	if (VerbosityLevel == Verbosity::Fatal)
	{
		HandleFatalError();
	}
}

void Log::HandleFatalError()
{
	if (Log::IsDebuggerAttached() == true)
	{
		__debugbreak();
	}
	else
	{
		throw std::runtime_error("FATAL ERROR encountered.");
	}
}

void Log::PrintTimeStampToConsoleWindow()
{
	time_t now = time(0);
	tm timeInfo;
	localtime_s(&timeInfo, &now);
	printf("[%d.%02d.%02d-%02d:%02d:%02d] ", timeInfo.tm_year + 1900, timeInfo.tm_mon + 1, timeInfo.tm_mday, timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
}

void Log::PrintTimeStampToOutputWindow()
{
	time_t now = time(0);
	tm timeInfo;
	localtime_s(&timeInfo, &now);
	char szBuffer[23];
	sprintf_s(szBuffer, "[%d.%02d.%02d-%02d:%02d:%02d] ", timeInfo.tm_year + 1900, timeInfo.tm_mon + 1, timeInfo.tm_mday, timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
	wchar_t wc[23];
	mbstowcs_s(nullptr, wc, szBuffer, _TRUNCATE);
	OutputDebugStringW(wc);
}

void Log::PrintTimeStampToTextFile(std::ofstream& OutStream)
{
	time_t now = time(0);
	tm timeInfo;
	localtime_s(&timeInfo, &now);
	char timeStampBuffer[36];
	sprintf_s(timeStampBuffer, "[%d.%02d.%02d-%02d:%02d:%02d] ", timeInfo.tm_year + 1900, timeInfo.tm_mon + 1, timeInfo.tm_mday, timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
	OutStream << timeStampBuffer;
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
	case Verbosity::Fatal:
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
	// Set the color to white.
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

const bool Log::IsDebuggerAttached()
{
	return (IsDebuggerPresent() != 0);
}
