
#include "Log.h"

// @TODO: Write in code for non-unicode stuff.

/*
 * Create categories that can then be dumped to individual txt files?
 * Also config setup to allow for output only, console only, text file.
 * Turn Log singleton into namespace?
 */

// @TODO: Remove VLD. Only here for testing.
#ifdef _DEBUG
//#include <vld.h>
#endif

int main()
{
	Log::GetInstance()->ResetTextColor();

	LOG_LEGACY(Error, "Testing an error level message\n");
	LOG_LEGACY(Default, "Back to default.\n");
	LOG_LEGACY(Warning, "This is a warning.\n");
	LOG_LEGACY(Debug, "Debug this thing.\n");
	LOG_LEGACY(Default, "Back to default.\n");

	LOG_DETAILED(Warning, "Test Detailed message.\n");
	
	Log::GetInstance()->OutputTimeStamp();
//	OutputDebugStringW(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");



	// New Log testing.
	LOG(SomeCategory, Debug, false, "Test %d thing.", 512);
	LOG(OtherCategory, Error, true, "Blah blah blah");




	Log::GetInstance()->ResetTextColor();

	system("PAUSE");
	return 0;
}
