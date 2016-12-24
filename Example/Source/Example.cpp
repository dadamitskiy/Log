/**
 * The MIT License (MIT)
 *
 * Copyright © Daniel Adamitskiy. All Rights Reserved.
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

#include <Log.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// Declare several categories.
DA_LOG_CATEGORY(OutWin, OutputWindow, Medium, All);
DA_LOG_CATEGORY(ConWinCat, ConsoleWindow, Low, All);
DA_LOG_CATEGORY(MyTxtFileCategory, TextFile, High, All);
DA_LOG_CATEGORY(MyAllCategory, All, Low, All);

int main(int argc, char* argv[])
{
	// Uncommenting the following/utilizing a fatal log with result in halting program execution
	// DA_LOG(OutWin, Fatal, "This type of log causes a break");

	// Test out logging to the output window.
	DA_LOG(OutWin, Debug, "Test Message for the output window.");
	DA_LOG(OutWin, Error, "Output %s message to the output window.", "this");
	DA_LOG(OutWin, Warning, "This is the %drd message.", 3);
	DA_LOG(OutWin, Info, "Last message to the output window.");

	// Test out logging to a console window.
	DA_LOG(ConWinCat, Debug, "Let's log some numbers to the console: %d %d %d %d.", 32, 23, 546, 65);
	DA_LOG(ConWinCat, Error, "This is a bad error message example.");
	DA_LOG(ConWinCat, Warning, "Now this would be a possible warning.");
	DA_LOG(ConWinCat, Info, "Guess we'll just go back to logging %s messages.", "default");

	// Test out logging to a text file.
	DA_LOG(MyTxtFileCategory, Debug, "Try logging the number %d to a text file.", 35);
	DA_LOG(MyTxtFileCategory, Warning, "Yay! I guess %s worked.", "it");
	DA_LOG(MyTxtFileCategory, Error, "Oh no, some error here.");
	DA_LOG(MyTxtFileCategory, Info, "Some default unimportant message.");

	// Test out logging to all output forms.
	DA_LOG(MyAllCategory, Debug, "Let's log this message to all %d log outputs.", 3);
	DA_LOG(MyAllCategory, Warning, "Guess it %s, as this message is on all %d areas.", "worked", 3);
	DA_LOG(MyAllCategory, Info, "Hey look, I'm just a normal message.");
	DA_LOG(MyAllCategory, Error, "This would log some error.");

	return 0;
}
