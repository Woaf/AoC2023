#pragma once

#include <vector>
#include <string>


using IntArray = std::vector<int32_t>;
using cIntArray = const std::vector<int32_t>;
using StrArray = std::vector<std::string>;
using cStrArray = const std::vector<std::string>;


namespace LX
{

enum class LineDataCombinator
{
	PARAM_AS_FIRST_DIGIT = 0,
	PARAM_AS_SECOND_DIGIT
};

enum class LineDataParseDirection
{
	FORWARD = 0, 
	REVERSE
};

class Utils
{
public:
	static int32_t SelectNumFromString(const std::string& iNumberStr) noexcept;

public:
	static cStrArray NumberStrs;
};

}
