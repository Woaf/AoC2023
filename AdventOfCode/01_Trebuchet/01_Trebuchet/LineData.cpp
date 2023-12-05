#include "LineData.h"


LX::LineData::LineData(const std::string& iRawLineStr) : 
	rawLineStr(iRawLineStr)
{
}


bool LX::LineData::HasData() const
{
	return dataPosition.has_value();
}


int32_t LX::LineData::GetData() const
{
	if (HasData())
	{
		return data;
	}
	return 0;
}


size_t LX::LineData::GetDataPosition() const
{
	if (HasData())
	{
		return dataPosition.value();
	}
	return std::string::npos;
}


int32_t LX::LineData::Combine(const LineData& other, LX::LineDataCombinator combinatorFlag) const
{
	if (!HasData() || !other.HasData())
	{
		return 0;
	}

	switch(combinatorFlag)
	{ 
		case LineDataCombinator::PARAM_AS_FIRST_DIGIT:	return other.GetData() * 10 + data;
		case LineDataCombinator::PARAM_AS_SECOND_DIGIT: return data * 10 + other.GetData();
		default:										return 0;
	}
}


void LX::LineData::ParseFromNumber(LX::LineDataParseDirection ParseDirection)
{
	if (ParseDirection == LX::LineDataParseDirection::FORWARD)
	{
		ParseFromNumberForward();
	}
	else
	{
		ParseFromNumberBackward();
	}
}


void LX::LineData::ParseFromString(LX::LineDataParseDirection ParseDirection)
{
	if (ParseDirection == LX::LineDataParseDirection::FORWARD)
	{
		ParseFromStringForward();
	}
	else
	{
		ParseFromStringBackward();
	}
}


void LX::LineData::ParseFromNumberForward()
{
	for (size_t i = 0; i < rawLineStr.length(); ++i)
	{
		if (std::isdigit(rawLineStr.at(i)))
		{
			dataPosition = i;
			data = static_cast<int32_t>(rawLineStr.at(i) - '0');
			break;
		}
	}
}


void LX::LineData::ParseFromNumberBackward()
{
	for (int32_t i = rawLineStr.length() - 1; i >= 0; --i)
	{
		if (std::isdigit(rawLineStr.at(i)))
		{
			dataPosition = i;
			data = static_cast<int32_t>(rawLineStr.at(i) - '0');
			break;
		}
	}
}


void LX::LineData::ParseFromStringForward()
{
	for (const std::string& strNum : LX::Utils::NumberStrs)
	{
		const size_t dataPos = rawLineStr.find(strNum);
		if (dataPos != std::string::npos && !dataPosition.has_value() ||
			dataPos != std::string::npos && dataPosition > dataPos)
		{
			dataPosition = dataPos;
			data = LX::Utils::SelectNumFromString(strNum);
		}
	}
}


void LX::LineData::ParseFromStringBackward()
{
	for (const std::string& strNum : LX::Utils::NumberStrs)
	{
		const size_t dataPos = rawLineStr.rfind(strNum);
		if (dataPos != std::string::npos && !dataPosition.has_value() ||
			dataPos != std::string::npos && dataPosition < dataPos)
		{
			dataPosition = dataPos;
			data = LX::Utils::SelectNumFromString(strNum);
		}
	}
}



