#include "Utils.h"

cStrArray LX::Utils::NumberStrs = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "zero" };


int32_t LX::Utils::SelectNumFromString(const std::string& iNumberStr) noexcept
{
	if (iNumberStr == "one")
		return 1;
	else if (iNumberStr == "two")
		return 2;
	else if (iNumberStr == "three")
		return 3;
	else if (iNumberStr == "four")
		return 4;
	else if (iNumberStr == "five")
		return 5;
	else if (iNumberStr == "six")
		return 6;
	else if (iNumberStr == "seven")
		return 7;
	else if (iNumberStr == "eight")
		return 8;
	else if (iNumberStr == "nine")
		return 9;
	else
		return 0;
}
