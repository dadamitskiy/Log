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

#ifndef _LOG_H_
#define _LOG_H_

#include <stdarg.h>
#include <stdio.h>
#include <crtdefs.h>
#include <fstream>

#if _DEBUG
#define DA_DEBUG	1
#define DA_RELEASE	0
#else
#define DA_DEBUG	0
#define DA_RELEASE	1
#endif

#define DA_LOG(Category, VerbosityLevel, OutputType, Detail, Format, ...) Log::Print(__FILE__, __FUNCTION__, __LINE__,  \
	#Category, Log::Verbosity::##VerbosityLevel, Log::OutputMethod::##OutputType, Log::DetailLevel::##Detail, Format,\
	__VA_ARGS__);

/*
 * A namespace containing the functions needed to log information to a console window, text file, or an output 
 * window. A namespace is used over a struct or class because there are no data members to store in a Log object. 
 */
namespace Log
{
	/* Verbosity levels for logging messages with varying importance. */
	namespace Verbosity
	{
		enum Type
		{
			Default,
			Debug,
			Warning,
			Error,
			Fatal,
		};
	}
	
	/* Different destinations to output to. */
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
	
	/* Varying levels of detail included in a log statement. */
	namespace DetailLevel
	{
		enum Type
		{
			Low,
			Medium,
			High,
		};
	}

	/* Print the desired message to the desired location in the desired detail. */
	void Print(const char* File, const char* Function, int LineNumber, const char* LogCategory, Verbosity::Type VerbosityLevel, OutputMethod::Type OutMethod, DetailLevel::Type Detail, const char* Format, ...);

	/* Handle encountering a fatal error. */
	void HandleFatalError();

	/* Print a timestamp in the following order: Year.Month.Day-Hour:Minute:Second */
	void PrintTimeStampToConsoleWindow();

	/* Print a timestamp to Visual Studio output window. */
	void PrintTimeStampToOutputWindow();

	/* Print a timestamp to a text file. */
	void PrintTimeStampToTextFile(std::ofstream& OutStream);

	/* Set the color of the console window text based on the verbosity level. */
	void SetTextColorToVerbosityLevel(Verbosity::Type InLevel);

	/* Reset the text color to white. */
	void ResetTextColor();

	/** Checks if the debugger is currently attached. */
	const bool IsDebuggerAttached();
}

#endif
