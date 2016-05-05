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

#include "Log.h"
#include <Windows.h>

/*
	Improvements Ideas:

	- Allow way to declare a log category and specify where it's output and detail level.
	- Define debug/release enable/disable levels in log category.
	- Asynchronous log thread(?) and thread safe.
	- Overriding log during release.
	- Debug only logging.
	- Fatal grabs callstack(?)
	- Add priorities of log(?)
	- Take out endl because '\n' is faster
	- No size limit to amount of character in msg.
	- Optimizations and speed comparisons.
	- Cross platform support. (Linux, Mac, Android, etc.)
	- Add asserts type in as well?
	- Cleanup code in in printing implementation. It could use some work.
	- Consider a design pattern implementation
		- Improve overall fatal error usage/code. 
*/

int main(int, const char*[])
{
	if (Log::IsDebuggerAttached())
	{
		DA_LOG(Test, Debug, ConsoleWindow, Low, "Detecting a debugger attached.");
	}
	
	// DA_LOG(Test, Fatal, All, Low, "Something bad is happening.");


	// Test out logging to the output window.
	DA_LOG(OutWin, Debug, OutputWindow, Medium, "Test Message for the output window.");
	DA_LOG(OutWin, Error, OutputWindow, Medium, "Output %s message to the output window.", "this");
	DA_LOG(OutWin, Warning, OutputWindow, Medium, "This is the %drd message.", 3);
	DA_LOG(OutWin, Default, OutputWindow, Medium, "Last message to the output window.");

	// Test out logging to a console window.
	DA_LOG(ConWinCat, Debug, ConsoleWindow, Low, "Let's log some numbers to the console: %d %d %d %d.", 32, 23, 546, 65);
	DA_LOG(ConWinCat, Error, ConsoleWindow, Low, "This is a bad error message example.");
	DA_LOG(ConWinCat, Warning, ConsoleWindow, Low, "Now this would be a possible warning.");
	DA_LOG(ConWinCat, Default, ConsoleWindow, Low, "Guess we'll just go back to logging %s messages.", "default");

	// Test out logging to a text file.
	DA_LOG(MyTxtFileCategory, Debug, TextFile, High, "Try logging the number %d to a text file.", 35);
	DA_LOG(MyTxtFileCategory, Warning, TextFile, High, "Yay! I guess %s worked.", "it");
	DA_LOG(MyTxtFileCategory, Error, TextFile, High, "Oh no, some error here.");
	DA_LOG(MyTxtFileCategory, Default, TextFile, High, "Some default unimportant message.");

	// Test out logging to all output forms.
	DA_LOG(MyAllCategory, Debug, All, Low, "Let's log this message to all %d log outputs.", 3);
	DA_LOG(MyAllCategory, Warning, All, Low, "Guess it %s, as this message is on all %d areas.", "worked", 3);
	DA_LOG(MyAllCategory, Default, All, Low, "Hey look, I'm just a normal message.");
	DA_LOG(MyAllCategory, Error, All, Low, "This must be some error.");

	system("PAUSE");
	return 0;
}
