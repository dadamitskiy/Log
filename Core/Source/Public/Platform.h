/**
 * The MIT License (MIT)
 *
 * Copyright � Daniel Adamitskiy. All Rights Reserved.
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

#if defined(_WIN32) && !defined(_WIN64)
	#define DA_PLATFORM_WINDOWS		1
	#define DA_PLATFORM_WIN32		1
	#define DA_PLATFORM_WIN64		0
	#define DA_PLATFORM_LINUX		0
	#define DA_PLATFORM_UNIX		0
	#define DA_PLATFORM_ANDROID		0
	#define DA_PLATFORM_APPLE		0
#elif defined(_WIN64)
	#define DA_PLATFORM_WINDOWS		1
	#define DA_PLATFORM_WIN32		0
	#define DA_PLATFORM_WIN64		1
	#define DA_PLATFORM_LINUX		0
	#define DA_PLATFORM_UNIX		0
	#define DA_PLATFORM_ANDROID		0
	#define DA_PLATFORM_APPLE		0
#elif defined(__linux__)
	#define DA_PLATFORM_WINDOWS		0
	#define DA_PLATFORM_WIN32		0
	#define DA_PLATFORM_WIN64		0
	#define DA_PLATFORM_LINUX		1
	#define DA_PLATFORM_UNIX		0
	#define DA_PLATFORM_ANDROID		0
	#define DA_PLATFORM_APPLE		0
#elif defined(__unix__)
	#define DA_PLATFORM_WINDOWS		0
	#define DA_PLATFORM_WIN32		0
	#define DA_PLATFORM_WIN64		0
	#define DA_PLATFORM_LINUX		0
	#define DA_PLATFORM_UNIX		1
	#define DA_PLATFORM_ANDROID		0
	#define DA_PLATFORM_APPLE		0
#elif defined(__ANDROID__)
	#define DA_PLATFORM_WINDOWS		0
	#define DA_PLATFORM_WIN32		0
	#define DA_PLATFORM_WIN64		0
	#define DA_PLATFORM_LINUX		0
	#define DA_PLATFORM_UNIX		0
	#define DA_PLATFORM_ANDROID		1
	#define DA_PLATFORM_APPLE		0
#elif defined(__APPLE__)
	#define DA_PLATFORM_WINDOWS		0
	#define DA_PLATFORM_WIN32		0
	#define DA_PLATFORM_WIN64		0
	#define DA_PLATFORM_LINUX		0
	#define DA_PLATFORM_UNIX		0
	#define DA_PLATFORM_ANDROID		0
	#define DA_PLATFORM_APPLE		1
#else
	#error Unknown platform detected.
#endif
