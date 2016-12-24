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

#pragma once

#include "Type.h"
#include "Platform.h"
#include "Module.h"
#include <vector>

namespace DA
{
namespace Core
{

class CORE_API CallStackFrame
{
public:

	/**
	 * @brief Constructor.
	 *
	 * @param address - Address of this frame.
	 * @param fileName - File name of this frame.
	 * @param functionName - The file name this frame is in.
	 * @param lineNumber - Line number the frame is on.
	 */
	explicit DA_FORCEINLINE CallStackFrame(const uint64 address, const int8* fileName, const int8* functionName, const int32 lineNumber)
		: address(address)
		, file_name(fileName)
		, function_name(functionName)
		, line_number(lineNumber)
	{
	}

	/**
	 * @brief Destructor.
	 */
	DA_FORCEINLINE ~CallStackFrame()
	{
	}

	/**
	 * @brief Gets this frame's address.
	 * 
	 * @return The address of the call stack frame.
	 */
	const DA_FORCEINLINE uint64 GetAddress() const { return address; }

	/**
	 * @brief Gets the file name for this frame.
	 *
	 * @return The file name of the frame.
	 */
	const DA_FORCEINLINE int8* GetFileName() const { return file_name; }

	/**
	 * @brief Gets this frame's function name.
	 *
	 * @return The function name of this frame.
	 */
	const DA_FORCEINLINE int8* GetFunctionName() const { return function_name; }

	/**
	 * @brief Gets this frame's line number.
	 *
	 * @return The line number of this frame.
	 */
	const DA_FORCEINLINE int32 GetLineNumber() const { return line_number; }

private:
	
	const uint64 address;
	
	const int8* file_name;
	
	const int8* function_name;
	
	const int32 line_number;
};

class CallStack
{
public:

	/**
	 * @brief Constructor.
	 */
	CORE_API CallStack();

	/**
	 * @brief Destructor.
	 */
	CORE_API ~CallStack();

	/**
	 * @brief Captures current call stack information.
	 *
	 * @return True on successful capture, false otherwise.
	 */
	CORE_API bool CaptureCallStackInfo();

	/**
	 * @brief Output call stack info and cleanup memory.
	 */
	CORE_API void OutputCallStackInfo();

	/**
	 * @brief Get the call stack frame info.
	 *
	 * @return Vector of call stack frames.
	 */
	DA_FORCEINLINE std::vector<CallStackFrame> GetCallStackInfo() const { return call_stack_frames; }

private:

	std::vector<CallStackFrame> call_stack_frames;
};

} // namespace Core
} // namespace DA
