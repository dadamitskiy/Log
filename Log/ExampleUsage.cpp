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

int main(int, const char*[])
{
	// Test out logging to the output window.
	LOG(OutWin, Debug, OutputWindow, High, "Test Message for the output window.");
	LOG(OutWin, Error, OutputWindow, Medium, "Output %s message to the output window.", "this");
	LOG(OutWin, Warning, OutputWindow, Low, "This is the %drd message.", 2);
	LOG(OutWin, Default, OutputWindow, Medium, "Last message to the output window.");

	// Test out logging to a console window.
	LOG(ConWinCat, Debug, ConsoleWindow, High, "Let's log some numbers to the console: %d %d %d %d.", 32, 23, 546, 65);
	LOG(ConWinCat, Error, ConsoleWindow, Medium, "This is a bad error message example.");
	LOG(ConWinCat, Warning, ConsoleWindow, Low, "Now this would be a possible warning.");
	LOG(ConWinCat, Default, ConsoleWindow, Low, "Guess we'll just go back to logging %s messages.", "default");

	// Test out logging to a text file.
	LOG(MyTxtFileCategory, Debug, TextFile, High, "Try logging the number %d to a text file.", 35);
	LOG(MyTxtFileCategory, Warning, TextFile, Medium, "Yay! I guess %s worked.", "it");
	LOG(MyTxtFileCategory, Error, TextFile, Medium, "Oh no, some error here.");
	LOG(MyTxtFileCategory, Default, TextFile, Low, "Some default unimportant message.");

	// Test out logging to all output forms.
	LOG(MyAllCategory, Debug, All, High, "Let's log this message to all %d log outputs.", 3);
	LOG(MyAllCategory, Warning, All, High, "It must have %s, as this message is on all %d areas.", "worked", 3);
	LOG(MyAllCategory, Default, All, Medium, "Hey look, I'm just a normal message.");
	LOG(MyAllCategory, Error, All, Low, "This must be some error.");

	system("PAUSE");
	return 0;
}
