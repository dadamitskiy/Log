/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Daniel Adamitskiy
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

#include "Log.h"
#include <Windows.h>

// @TODO: Write in code for non-unicode stuff.
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

	Log::ResetTextColor();

	system("PAUSE");
	return 0;
}
