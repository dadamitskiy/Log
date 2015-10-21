
#include "Log.h"
#include <Windows.h>
#include <string>

#include <iostream>
#include <fstream>

// @TODO: Write in code for non-unicode stuff.
// @TODO: Turn Log singleton into namespace? Singleton not really thread safe by default.

// @TODO: Remove VLD. Only here for testing.
#ifdef _DEBUG
//#include <vld.h>
#endif

int main()
{
	// Test out loggin to the output window.
	LOG(TestCat01, Debug, OutputWindow, High, "TestMessage");
	LOG(TestCat01, Debug, OutputWindow, Low, "TestMessage %d", 2);
	LOG(TestCat01, Debug, OutputWindow, Medium, "TestMessage %s", "Three");

	// Test out logging to a console window.
	LOG(Test01, Debug, ConsoleWindow, High, "Test %d %d %d %d sadfj", 32, 23, 546, 65);
	LOG(dfg, Error, ConsoleWindow, Medium, "Testing an error level message");
	LOG(sfd, Default, ConsoleWindow, Low, "Back to default.");
	LOG(asdf, Warning, ConsoleWindow, Low, "This is a warning.");
	LOG(afsdf, Debug, ConsoleWindow, Low, "Debug this thing.");
	LOG(SomeCategory, Debug, ConsoleWindow, Low, "Test %d thing.", 512);
	LOG(OtherCategory, Error, ConsoleWindow, High, "Blah blah blah");

	// Test out logging to a text file.
	LOG(NonCategory, Debug, TextFile, High, "Test thing string stuff %d.", 35);
	LOG(NonCategory, Warning, TextFile, Medium, "Test thing string stuff %s.", "blah");
	LOG(NonCategory, Error, TextFile, Low, "Test thing string stuff.");
	LOG(NonCategory, Default, TextFile, Low, "Test thing string stuff.");

	Log::GetInstance()->ResetTextColor();

	system("PAUSE");
	return 0;
}
