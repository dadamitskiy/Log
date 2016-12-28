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

#include "LogCategory.h"

#define DA_LOG_CATEGORY(categoryName, outputType, detail, inConfig)																			\
	extern struct LogCategory##categoryName : public DA::Log::LogCategory																	\
	{																																		\
		explicit DA_FORCEINLINE LogCategory##categoryName()																					\
			: LogCategory(#categoryName, DA::Log::OutputMethod::outputType, DA::Log::DetailLevel::detail, DA::Log::BuildConfig::inConfig)	\
		{																																	\
		}																																	\
		virtual ~LogCategory##categoryName()																								\
		{																																	\
		}																																	\
	} categoryName;																															\
	LogCategory##categoryName categoryName;

#define DA_LOG(categoryName, VerbosityLevel, Format, ...) DA::Log::Logger::GetInstance().Log(categoryName, __FILE__, __FUNCTION__, __LINE__,\
	DA::Log::Verbosity::VerbosityLevel, Format, __VA_ARGS__);

namespace DA
{
namespace Log
{

class LOG_API Logger
{
public:
	
	/**
	 * @brief Get the Logger class instance.
	 *
	 * @return Singleton instance of the logger class.
	 */
	static DA_FORCEINLINE Logger& GetInstance()
	{
		static Logger instance;
		return instance;
	}

	/**
	 * @brief Log a message within the contraints specified by the given log category.
	 *
	 * @param logCategory - Log category to log with.
	 * @param fileNameFullPath - Name of file being logged from, including the full path.
	 * @param functionName - Name of function being logged from.
	 * @param lineNumber - Line number being logged from.
	 * @param verbosityLevel - Verbosity to log with.
	 * @param format - Message formatting.
	 * @param ... - Variable arguments to be logged.
	 */
	void Log(const LogCategory& logCategory, int8* fileNameFullPath, const int8* functionName, const int32 lineNumber, Verbosity verbosityLevel, const int8* format, ...);

private:

	/**
	 * @brief Constructor.
	 */
	Logger();

	/**
	 * @brief Destructor.
	 */
	~Logger();

	/**
	 * @brief Deleted copy constructor.
	 *
	 * @param logInstance - Logger instance to copy.
	 */
	Logger(const Logger& logInstance) = delete;

	/**
	 * @brief Deleted assignment operator.
	 *
	 * @param logInstance - Logger instance.
	 */
	void operator=(const Logger& logInstance) = delete;

	/**
	 * @brief Gets the name of a file from a full path.
	 *
	 * @param fileNameFullPath - A file name that includes the full path.
	 * 
	 * @return The file name without the full path.
	 */
	const int8* GetFileNameFromFullPath(int8* fileNameFullPath);

	/**
	 * @brief Gets the text representation of a verbosity level.
	 *
	 * @param verbosityLevel - The verbosity level.
	 * 
	 * @return A text representation of the passed in verbosity level.
	 */
	const int8* GetVerbosityAsText(Verbosity verbosityLevel) const;

	/**
	 * @brief Handles encountering a fatal error log.
	 */
	void HandleFatalError();

	/**
	 * @brief Logs a timestamp in [Year.Month.Day-Hour:Minute:Second] order.
	 *
	 * @param outputMethod - Location to output timestamp to.
	 * @param outputFile - File to output to if a text file is the desired end location.
	 */
	void LogTimeStamp(OutputMethod ouputMethod, FILE* outputFile = nullptr);

	/**
	 * @brief Sets the color of the console window text based on the verbosity level.
	 *
	 * @param verbosityLevel - Level of verbosity.
	 */
	void SetTextColorToVerbosityLevel(Verbosity verbositLevel);

	/**
	 * @brief Reset the text color to white.
	 */
	void ResetTextColor();

	/**
	 * @brief Checks if the debugger is currently attached.
	 */
	const bool IsDebuggerAttached();
};

} // namespace Log
} // namespace DA
