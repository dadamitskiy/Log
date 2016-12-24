/**
 * The MIT License (MIT)
 *
 * Copyright © Daniel Adamitskiy. All Rights Reserved.
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

#include "Logger.h"
#include <ctime>
#include <direct.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace DA
{
namespace Log
{

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::Log(const LogCategory& logCategory, int8* fileNameFullPath, const int8* functionName, const int32 lineNumber, Verbosity verbosityLevel, const int8* format, ...)
{
	// Early out to check that we don't log during specific configs.
	if ((logCategory.GetBuildConfig() == BuildConfig::Debug && !DA_BUILD_DEBUG) || (logCategory.GetBuildConfig() == BuildConfig::Release && !DA_BUILD_RELEASE))
	{
		return;
	}
	
	if (logCategory.GetOutputMethod() == OutputMethod::ConsoleWindow || logCategory.GetOutputMethod() == OutputMethod::All)
	{
		SetTextColorToVerbosityLevel(verbosityLevel);
	}

	FILE* file = nullptr;
	if (logCategory.GetOutputMethod() == OutputMethod::TextFile || logCategory.GetOutputMethod() == OutputMethod::All)
	{
		// If an OutputLogs folder doesn't exist, create one.
		DWORD fileType = GetFileAttributes(L"OutputLogs");

		if (fileType == INVALID_FILE_ATTRIBUTES && (fileType & FILE_ATTRIBUTE_DIRECTORY))
		{
			_mkdir("OutputLogs");
		}

		char outputFileName[512];
		sprintf_s(outputFileName, DA_ARRAYSIZE(outputFileName), "OutputLogs/%s.txt", logCategory.GetCategoryName());

		// Append the data to a text file.
		file = IO::OpenFile(outputFileName, IO::FileAccessMode::Append);
	}

	if (logCategory.GetDetailLevel() == DetailLevel::High)
	{
		LogTimeStamp(logCategory.GetOutputMethod(), file);
	}

	int8 output[1024];
	const size_t outputArraySize = DA_ARRAYSIZE(output);

	// Get just the filename without the full path.
	const int8* fileName = GetFileNameFromFullPath(fileNameFullPath);

	if (logCategory.GetDetailLevel() != DetailLevel::Low)
	{
		sprintf_s(output, outputArraySize, "[File: %s, Function: %s, Line: %d] ", fileName, functionName, lineNumber);

		int8* newStartPosition = strchr(output, ']') + 2;
		size_t bufferCount = outputArraySize - (newStartPosition - output);
		sprintf_s(&output[outputArraySize - bufferCount], bufferCount, "%s %s - ", logCategory.GetCategoryName(), GetVerbosityAsText(verbosityLevel));

		newStartPosition = strchr(output, '-') + 2;
		bufferCount = outputArraySize - (newStartPosition - output);
		
		va_list ap;
		va_start(ap, format);

		vsprintf_s(&output[outputArraySize - bufferCount], bufferCount, format, ap);

		va_end(ap);
	}
	else
	{
		// Copy everything but the actual log messsage
		sprintf_s(output, outputArraySize, "%s %s - ", logCategory.GetCategoryName(), GetVerbosityAsText(verbosityLevel));

		int8* newStartPosition = strchr(output, '-') + 2;

		// Now copy the message
		va_list ap;
		va_start(ap, format);

		const size_t bufferCount = outputArraySize - (newStartPosition - output);
		vsprintf_s(&output[outputArraySize - bufferCount], bufferCount, format, ap);

		va_end(ap);
	}

	// Log the message to the correct location
	if (logCategory.GetOutputMethod() == OutputMethod::ConsoleWindow || logCategory.GetOutputMethod() == OutputMethod::All)
	{
		printf("%s\n", output);
	}

	if (logCategory.GetOutputMethod() == OutputMethod::OutputWindow || logCategory.GetOutputMethod() == OutputMethod::All)
	{
		OutputDebugStringA(output);
		OutputDebugStringA("\n");
	}

	if (logCategory.GetOutputMethod() == OutputMethod::TextFile || logCategory.GetOutputMethod() == OutputMethod::All)
	{
		if (file == nullptr)
		{
			return;
		}

		IO::Put(file, output);
		IO::Put(file, "\n");
		IO::FlushStream(file);
		IO::CloseFile(file);
	}

	// After we're done logging information, ensure fatal errors are properly handled.
	if (verbosityLevel == Verbosity::Fatal)
	{
		HandleFatalError();
	}
}

const int8* Logger::GetFileNameFromFullPath(int8* fileNameFullPath)
{
	// Get just the filename without the full path.
	int8* fileName = strrchr(fileNameFullPath, '\\') + 1;
	
	if (fileName == nullptr)
	{
		fileName = "Unknown";
	}

	return fileName;
}

const int8* Logger::GetVerbosityAsText(Verbosity verbosityLevel) const
{
	if (verbosityLevel == Verbosity::Info)
	{
		return "Info";
	}
	else if (verbosityLevel == Verbosity::Debug)
	{
		return "Debug";
	}
	else if (verbosityLevel == Verbosity::Warning)
	{
		return "Warning";
	}
	else if (verbosityLevel == Verbosity::Error)
	{
		return "Error";
	}
	else if (verbosityLevel == Verbosity::Fatal)
	{
		return "Fatal";
	}
	else
	{
		return "";
	}
}

void Logger::HandleFatalError()
{
	if (IsDebuggerAttached())
	{
		__debugbreak();
	}
	else
	{
		DA::Core::CallStack callstack;
		if (callstack.CaptureCallStackInfo())
		{
			callstack.OutputCallStackInfo();
		}

		// Crash the program.
		volatile int* a = reinterpret_cast<volatile int*>(NULL);
		*a = 1;
	}
}

void Logger::LogTimeStamp(OutputMethod outputMethod, FILE* outputFile)
{
	time_t now = time(0);
	tm timeInfo;
	localtime_s(&timeInfo, &now);

	char buffer[23]; // 22 characters + null terminator
	sprintf_s(buffer, DA_ARRAYSIZE(buffer), "[%d.%02d.%02d-%02d:%02d:%02d] ", timeInfo.tm_year + 1900, timeInfo.tm_mon + 1, timeInfo.tm_mday, timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);

	if (outputMethod == OutputMethod::ConsoleWindow || outputMethod == OutputMethod::All)
	{
		printf("%s", buffer);
	}
	
	if (outputMethod == OutputMethod::OutputWindow || outputMethod == OutputMethod::All)
	{
		OutputDebugStringA(buffer);
	}

	if (outputMethod == OutputMethod::TextFile || outputMethod == OutputMethod::All)
	{
		IO::Put(outputFile, buffer);
	}
}

void Logger::SetTextColorToVerbosityLevel(Verbosity verbositLevel)
{
	switch (verbositLevel)
	{
	case Verbosity::Debug:
		{
			// Set the color to green.
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		}
		break;
	case Verbosity::Warning:
		{
			// Set the color to yellow.
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		}
		break;
	case Verbosity::Error:
		{
			// Set the color to red.
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		}
		break;
	case Verbosity::Fatal:
		{
			// Set the color to red.
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		}
		break;
	case Verbosity::Info:
		// Intended fallthrough.
	default:
		{
			// Default it to a white color.
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		break;
	}
}

void Logger::ResetTextColor()
{
	// Set the color to white.
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

const bool Logger::IsDebuggerAttached()
{
	// Checking return != 0 to eliminate warning.
	return IsDebuggerPresent() != 0;
}

} // namespace Log
} // namespace DA
