
#ifndef _LOG_H_
#define _LOG_H_

#include <Windows.h>
#include <string>

#define LOG(VerbosityLevel, Msg) \
	Log::GetInstance()->SetTextColorToVerbosityLevel(Verbosity::##VerbosityLevel); \
	Log::GetInstance()->Print(Msg);

#define LOG_DETAILED(VerbosityLevel, Msg) \
	Log::GetInstance()->SetTextColorToVerbosityLevel(Verbosity::##VerbosityLevel); \
	Log::GetInstance()->PrintTimeStamp(); \
	Log::GetInstance()->Print(Msg);

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



	// ...
	void Print(std::string szMessage);



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
