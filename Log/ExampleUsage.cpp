
#include "Log.h"
#include <Windows.h>
#include <string>

#include <iostream>
#include <fstream>

// @TODO: Write in code for non-unicode stuff.

/*
 * Create categories that can then be dumped to individual txt files?
 * Also config setup to allow for output only, console only, text file.
 * Turn Log singleton into namespace? Singleton not really thread safe by default.
 * Add file number and line __LINE__, __FUNC__, etc...
 */

// @TODO: Remove VLD. Only here for testing.
#ifdef _DEBUG
//#include <vld.h>
#endif

int main()
{
	Log::GetInstance()->OutputTimeStamp();

	//LOG(Test01, Debug, OutputWindow, High, "Test %d %d %d %d sadfj", 32, 23, 546, 65);
	//LOG(Test01, Default, OutputWindow, High, "Test %s sadfj", "ONE");

	LOG(Test01, Debug, ConsoleWindow, High, "Test %d %d %d %d sadfj", 32, 23, 546, 65);
	LOG(dfg, Error, ConsoleWindow, Medium, "Testing an error level message");
	LOG(sfd, Default, ConsoleWindow, Low, "Back to default.");

	LOG(asdf, Warning, ConsoleWindow, Low, "This is a warning.");
	LOG(afsdf, Debug, ConsoleWindow, Low, "Debug this thing.");

	LOG(SomeCategory, Debug, ConsoleWindow, Low, "Test %d thing.", 512);
	LOG(OtherCategory, Error, ConsoleWindow, High, "Blah blah blah");


	LOG(NonCategory, Debug, TextFile, High, "Test thing string stuff %d.", 35);
	LOG(NonCategory, Warning, TextFile, Medium, "Test thing string stuff %s.", "blah");
	LOG(NonCategory, Error, TextFile, Low, "Test thing string stuff.");
	LOG(NonCategory, Default, TextFile, Low, "Test thing string stuff.");

	Log::GetInstance()->ResetTextColor();

	system("PAUSE");
	return 0;
}
