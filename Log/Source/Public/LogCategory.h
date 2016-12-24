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

#include <Core.h>
#include "Module.h"

namespace DA 
{ 
namespace Log 
{

/** 
 * @brief Different destinations to output to. 
 */
enum class OutputMethod : int8
{
	All,
	ConsoleWindow,
	OutputWindow,
	TextFile,
};

/** 
 * @brief Varying levels of detail included in a log statement. 
 */
enum class DetailLevel : int8
{
	Low,
	Medium,
	High,
};

/** 
 * @brief Configurations where the logging is allowed to occur. 
 */
enum class BuildConfig : int8
{
	Debug,
	Release,
	All
};

/** 
 * @brief Verbosity levels for logging messages with varying importance. 
 */
enum class Verbosity : int8
{
	Info,
	Debug,
	Warning,
	Error,
	Fatal,
};

/** 
 * @brief Stores log category info in the map of categories. 
 */
class LOG_API LogCategory
{
public:

	/**
	 * @brief Explicit constructor.
	 *
	 * @param categoryName - Name of this category.
	 * @param outputMethod - Valid output methods for this category.
	 * @param detailLevel - Detail level for this category.
	 * @param inConfig - Valid solution configurations for this category to log with.
	 */
	DA_FORCEINLINE LogCategory(const int8* categoryName, OutputMethod outputMethod, DetailLevel detailLevel, BuildConfig inConfig);

	/**
	 * @brief Gets the category name for this category.
	 *
	 * @return This category's name.
	 */
	DA_FORCEINLINE const int8* GetCategoryName() const;

	/**
	 * @brief Gets the desired output method for this category.
	 *
	 * @return This category's output method.
	 */
	DA_FORCEINLINE const OutputMethod GetOutputMethod() const;

	/**
	 * @brief Gets the desired detail level for this category.
	 *
	 * @return This category's detail level.
	 */
	DA_FORCEINLINE const DetailLevel GetDetailLevel() const;

	/**
	 * @brief Gets the desired build config for this category.
	 *
	 * @return This category's build config.
	 */
	DA_FORCEINLINE const BuildConfig GetBuildConfig() const;


private:

	const int8* category_name;

	const OutputMethod output_method;

	const DetailLevel detail_level;

	const BuildConfig build_config;
};

DA_FORCEINLINE LogCategory::LogCategory(const int8* categoryName, OutputMethod outputMethod, DetailLevel detailLevel, BuildConfig inConfig)
	: category_name(categoryName)
	, output_method(outputMethod)
	, detail_level(detailLevel)
	, build_config(inConfig)
{
}

DA_FORCEINLINE const OutputMethod LogCategory::GetOutputMethod() const
{ 
	return output_method; 
}

DA_FORCEINLINE const DetailLevel LogCategory::GetDetailLevel() const
{ 
	return detail_level; 
}

DA_FORCEINLINE const BuildConfig LogCategory::GetBuildConfig() const
{ 
	return build_config; 
}

DA_FORCEINLINE const int8* LogCategory::GetCategoryName() const
{ 
	return category_name; 
}

} // namespace Log
} // namespace DA
