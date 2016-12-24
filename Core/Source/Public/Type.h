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

#include "Platform.h"

typedef char				int8;
typedef short				int16;
typedef int					int32;
typedef long long			int64;

typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef unsigned long long	uint64;

typedef void*				v32;

typedef wchar_t				wint8;

#if DA_PLATFORM_WINDOWS
	#define DA_CDELC				__cdecl
	#define DA_STDCALL				__stdcall
	#define DA_INLINE				inline
	#define DA_FORCEINLINE			__forceinline
	#define DA_FORCENOINLINE		__declspec(noinline)
	#define DA_DEPRECATED(Msg)		__declspec(deprecated(Msg))
	#define DA_ARRAYSIZE(x)			_countof(x)  
#else
	#define DA_CDELC
	#define DA_STDCALL
	#define DA_INLINE
	#define DA_FORCEINLINE
	#define DA_FORCENOINLINE
	#define DA_DEPRECATED(Msg)
	#define DA_ARRAYSIZE(x)
#endif
