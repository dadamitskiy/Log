/**
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

#ifndef __LOG_H__
#define __LOG_H__

#include <stdarg.h>
#include <stdio.h>
#include <crtdefs.h>
#include <fstream>
#include <unordered_map>
#include <string>

#define DA_LOG_MAJOR_VERSION 1
#define DA_LOG_MINOR_VERSION 7

#define DA_DECLARE_LOG_CATEGORY(Category, OutputType, Detail) DA::Log::GetInstance().DeclareLogCategory(#Category, DA::OutputMethod::##OutputType, DA::DetailLevel::##Detail);
#define DA_LOG(Category, VerbosityLevel, Format, ...) DA::Log::GetInstance().Print(__FILE__, __FUNCTION__, __LINE__, #Category, DA::Verbosity::##VerbosityLevel, Format, __VA_ARGS__);

namespace DA
{
	/** Verbosity levels for logging messages with varying importance. */
	namespace Verbosity
	{
		enum Type
		{
			Info,
			Debug,
			Warning,
			Error,
			Fatal,
		};
	}
	
	/** Different destinations to output to. */
	namespace OutputMethod
	{
		enum Type
		{
			All,
			ConsoleWindow,
			OutputWindow,
			TextFile,
		};
	}
	
	/** Varying levels of detail included in a log statement. */
	namespace DetailLevel
	{
		enum Type
		{
			Low,
			Medium,
			High,
		};
	}

	/** Struct to store Log category info in the map of categories. */
	struct LogCategory
	{
		OutputMethod::Type mOutputMethod;
		DetailLevel::Type mDetailLevel;

		LogCategory() : 
			mOutputMethod(OutputMethod::All), 
			mDetailLevel(DetailLevel::High)
		{
		}

		LogCategory(OutputMethod::Type OutMethod, DetailLevel::Type Detail) : 
			mOutputMethod(OutMethod),
			mDetailLevel(Detail)
		{
		}
	};

	class Log
	{
	public:

		Log(const Log&) = delete;
		void operator=(const Log&) = delete;

		/** Return the singleton instance of this Log class. */
		static __forceinline Log& GetInstance()
		{
			static Log instance;
			return instance;
		}

		/** Declare a log category. */
		void DeclareLogCategory(const char* LogCategory, OutputMethod::Type OutMethod, DetailLevel::Type Detail);

		/** Print the desired message to the desired location in the desired detail. */
		void Print(const char* File, const char* Function, int LineNumber, const char* LogCategory, Verbosity::Type VerbosityLevel, const char* Format, ...);

	private:

		Log() = default;
		~Log() = default;

		/** Print to the console window. */
		void PrintToConsoleWindow(const char* File, const char* Function, int LineNumber, const char* LogCategory, Verbosity::Type VerbosityLevel, DetailLevel::Type Detail, const char* Format, va_list Args);

		/** Print to the Visual Studio output window. */
		void PrintToOutputWindow(const char* File, const char* Function, int LineNumber, const char* LogCategory, Verbosity::Type VerbosityLevel, DetailLevel::Type Detail, const char* Format, va_list Args);

		/** Print to the specified Log Category text file. */
		void PrintToTextFile(const char* File, const char* Function, int LineNumber, const char* LogCategory, Verbosity::Type VerbosityLevel, DetailLevel::Type Detail, const char* Format, va_list Args);

		/** Handle encountering a fatal error. */
		void HandleFatalError();

		/** Print a timestamp in the following order: Year.Month.Day-Hour:Minute:Second */
		void PrintTimeStampToConsoleWindow();

		/** Print a timestamp to Visual Studio output window. */
		void PrintTimeStampToOutputWindow();

		/** Print a timestamp to a text file. */
		void PrintTimeStampToTextFile(std::ofstream& OutStream);

		/** Set the color of the console window text based on the verbosity level. */
		void SetTextColorToVerbosityLevel(Verbosity::Type InLevel);

		/** Reset the text color to white. */
		void ResetTextColor();

		/** Checks if the debugger is currently attached. */
		const bool IsDebuggerAttached();

		/** Checks Log Category container if a log category already exists. */
		const bool DoesLogCategoryExist(const char* Category) const;

		/** The unordered map containing all log categories. */
		std::unordered_map<std::string, LogCategory> mLogCategories;
	};

} // DA

#endif // __LOG_H__
