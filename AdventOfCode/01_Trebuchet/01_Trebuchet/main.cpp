#include <iostream>
#include <fstream>
#include <istream>
#include <numeric>
#include <algorithm>
#include <optional>

#include "Utils.h"
#include "LineData.h"


int32_t GetFirstDigitInLine(const std::string& iLine)
{
	LX::LineData numDataForward{ iLine };
	numDataForward.ParseFromNumber(LX::LineDataParseDirection::FORWARD);
	LX::LineData strDataForward{ iLine };
	strDataForward.ParseFromString(LX::LineDataParseDirection::FORWARD);

	int32_t firstDigit = 0;
	if (numDataForward.HasData() && strDataForward.HasData())
	{
		if (numDataForward.GetDataPosition() < strDataForward.GetDataPosition())
		{
			firstDigit = numDataForward.GetData();
		}
		else
		{
			firstDigit = strDataForward.GetData();
		}
	}
	else if (numDataForward.HasData() && !strDataForward.HasData())
	{
		firstDigit = numDataForward.GetData();
	}
	else if (!numDataForward.HasData() && strDataForward.HasData())
	{
		firstDigit = strDataForward.GetData();
	}
	else
	{
		std::cout << "No data found for first digit - bad row data";
	}

	return firstDigit;
}


int32_t GetSecondDigitInLine(const std::string& iLine)
{
	LX::LineData numDataReverse{ iLine };
	numDataReverse.ParseFromNumber(LX::LineDataParseDirection::REVERSE);
	LX::LineData strDataReverse{ iLine };
	strDataReverse.ParseFromString(LX::LineDataParseDirection::REVERSE);

	int32_t secondDigit = 0;
	if (numDataReverse.HasData() && strDataReverse.HasData())
	{
		if (numDataReverse.GetDataPosition() > strDataReverse.GetDataPosition())
		{
			secondDigit = numDataReverse.GetData();
		}
		else
		{
			secondDigit = strDataReverse.GetData();
		}
	}
	else if (numDataReverse.HasData() && !strDataReverse.HasData())
	{
		secondDigit = numDataReverse.GetData();
	}
	else if (!numDataReverse.HasData() && strDataReverse.HasData())
	{
		secondDigit = strDataReverse.GetData();
	}
	else
	{
		std::cout << "No data found for second digit - bad row data";
	}

	return secondDigit;
}


int32_t ParseLine_Str(const std::string& iLine)
{
	const int32_t firstDigit = GetFirstDigitInLine(iLine);
	const int32_t secondDigit = GetSecondDigitInLine(iLine);

	return 10 * firstDigit + secondDigit;
}


IntArray GetCalibrationValues()
{
	std::ifstream infile("rawdata.txt");
	if (!infile.is_open())
		return IntArray();

	IntArray results;
	std::string line;
	while (std::getline(infile, line))
	{
		results.emplace_back(ParseLine_Str(line));
	}
	return results;
}


int main()
{
	cIntArray calibrationData = GetCalibrationValues();
	std::cout << "The sum of all calibration data is: " << accumulate(calibrationData.begin(), calibrationData.end(), 0) << std::endl;

	return 0;
}
