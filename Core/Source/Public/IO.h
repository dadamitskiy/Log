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
#include <cstdio>

namespace DA
{
namespace IO 
{

enum class FileAccessMode : int8
{
	Read,
	Write,
	Append,
	ReadUpdate,
	WriteUpdate,
	AppendUpdate,
};

/**
 * @brief Opens a file for a given file access mode.
 * 
 * @param fileName - Name of the file to open.
 * @param fileAccessMode - Access mode to open the file with.
 *
 * @return A pointer to the opened file, or nullptr if the operation wasn't valid.
 */
static FILE* OpenFile(const char* fileName, FileAccessMode fileAccessMode)
{
	FILE* stream = nullptr;
	int32 error = 0;

	switch (fileAccessMode)
	{
	case FileAccessMode::Read:
		{
			error = fopen_s(&stream, fileName, "r");
		}
		break;
	case FileAccessMode::Write:
		{
			error = fopen_s(&stream, fileName, "w");
		}
		break;
	case FileAccessMode::Append:
		{
			error = fopen_s(&stream, fileName, "a");
		}
		break;
	case FileAccessMode::ReadUpdate:
		{
			error = fopen_s(&stream, fileName, "r+");
		}
		break;
	case FileAccessMode::WriteUpdate:
		{
			error = fopen_s(&stream, fileName, "w+");
		}
		break;
	case FileAccessMode::AppendUpdate:
		{
			error = fopen_s(&stream, fileName, "a+");
		}
		break;
	default:
		// We should never enter here.
		break;
	}

	return stream;
}

/**
 * @brief Flushes a given stream.
 *
 * @param streamToFlush - The stream to flush.
 *
 * @return True if the stream was successfully flushed, false otherwise.
 */
static inline bool FlushStream(FILE* streamToFlush)
{
	return (fflush(streamToFlush) == 0) ? true : false;
}

/**
 * @brief Writes out a buffer to a given file.
 *
 * @param stream - File to output to.
 * @param buffer - Contents to output to given stream.
 *
 * @return True on successfully outputing to the file, false otherwise.
 */
static inline bool Put(FILE* stream, const char* buffer)
{
	return (fputs(buffer, stream) >= 0) ? true : false;
}

/**
 * @brief Close a given file stream.
 *
 * @param streamToClose - File stream to close.
 *
 * @return True on successfully closing the file, false otherwise.
 */
static inline bool CloseFile(FILE* streamToClose)
{
	return (fclose(streamToClose) == 0) ? true : false;
}

} // namespace IO
} // namespace DA
