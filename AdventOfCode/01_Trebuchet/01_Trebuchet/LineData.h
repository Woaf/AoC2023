#pragma once

#include <string>
#include <optional>
#include "Utils.h"

namespace LX
{

class LineData
{
public:
	LineData(const std::string& iRawLineStr);

	bool HasData() const;
	int32_t GetData() const;
	size_t GetDataPosition() const;

	int32_t Combine(const LineData& other, LX::LineDataCombinator combinatorFlag = LX::LineDataCombinator::PARAM_AS_SECOND_DIGIT) const;

	void ParseFromNumber(LX::LineDataParseDirection ParseDirection);
	void ParseFromString(LX::LineDataParseDirection ParseDirection);

protected:
	void ParseFromNumberForward();
	void ParseFromNumberBackward();

	void ParseFromStringForward();
	void ParseFromStringBackward();

private:
	std::string rawLineStr;

	std::optional<size_t> dataPosition;
	int32_t data = 0;
};

}



