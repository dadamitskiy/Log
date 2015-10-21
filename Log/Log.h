
#ifndef _LOG_H_
#define _LOG_H_

#include <stdarg.h>
#include <stdio.h>
#include <crtdefs.h>

#define LOG(Category, VerbosityLevel, OutputType, Detail, Format, ...) \
	Log::GetInstance()->Print(__FILE__, __FUNCTION__, __LINE__, #Category, Verbosity::##VerbosityLevel, OutputMethod::##OutputType, DetailLevel::##Detail, Format, __VA_ARGS__);

namespace Verbosity
{
	enum Type
	{
		Default,
		Debug,
		Warning,
		Error,
	};
}

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

namespace DetailLevel
{
	enum Type
	{
		Low,
		Medium,
		High,
	};
}

/*
 * 
 */
class Log
{
public:
	
	/* Singleton implementation. */
	static Log* GetInstance();

	/* Print the desired message to the desired location in the desired detail. */
	void Print(const char* File, const char* Function, int LineNumber, const char* LogCategory, Verbosity::Type VerbosityLevel, OutputMethod::Type OutMethod, DetailLevel::Type Detail, const char* Format, ...);

	/* Print a timestamp in the following order: Year.Month.Day-Hour:Minute:Second */
	void PrintTimeStamp();
	/* Output a timestamp to Visual Studio output window. */
	void OutputTimeStamp();

	/* Set the color of the console window text based on the verbosity level. */
	void SetTextColorToVerbosityLevel(Verbosity::Type InLevel);

	/* Reset the text color to white. */
	void ResetTextColor();

private:

	Log() = default;
	~Log() = default;
};

#endif
