
#include <Windows.h>
#include "Log.h"
#include <iostream>

// @TODO: Write in code for non-unicode stuff.

// @TODO: Remove VLD. Only here for testing.
#ifdef _DEBUG
//#include <vld.h>
#endif

int main()
{
	Log::GetInstance()->ResetTextColor();

	LOG(Error, "Testing an error level message\n");
	LOG(Default, "Back to default.\n");
	LOG(Warning, "This is a warning.\n");
	LOG(Debug, "Debug this thing.\n");
	LOG(Default, "Back to default.\n");

	LOG_DETAILED(Warning, "Test Detailed message.\n");
	
	Log::GetInstance()->OutputTimeStamp();
	OutputDebugStringW(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");

	Log::GetInstance()->ResetTextColor();

	system("PAUSE");
	return 0;
}
