
#ifndef _LOG_H_
#define _LOG_H_

#include <string>
#include <stdarg.h>

#define LOG_LEGACY(VerbosityLevel, Msg) \
	Log::GetInstance()->SetTextColorToVerbosityLevel(Verbosity::##VerbosityLevel); \
	Log::GetInstance()->Print(Msg);

#define LOG_DETAILED(VerbosityLevel, Msg) \
	Log::GetInstance()->SetTextColorToVerbosityLevel(Verbosity::##VerbosityLevel); \
	Log::GetInstance()->PrintTimeStamp(); \
	Log::GetInstance()->Print(Msg);

#define LOG(Category, VerbosityLevel, bAddTimestamp, Format, ...) \
	Log::GetInstance()->SetTextColorToVerbosityLevel(Verbosity::##VerbosityLevel); \
	if (bAddTimestamp) { Log::GetInstance()->PrintTimeStamp(); } \
	Log::GetInstance()->Print(Format, __VA_ARGS__);

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

/*
 * 
 */
class Log
{
public:
	
	/* Singleton implementation. */
	static Log* GetInstance();



	// ... To REMOVE ...
	void Print(std::string szMessage);
	// Final Print
	void Print(const char* Format, ...);


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
