#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <optional>


using IntArray = std::vector<int32_t>;
using cIntArray = const std::vector<int32_t>;
using StrArray = std::vector<std::string>;
using cStrArray = const std::vector<std::string>;


static cStrArray NumberStrs = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "zero"};


struct ParsedLineData
{
	std::optional<size_t> dataPosition;
	int32_t data = 0;
};


int32_t ParseLine(const std::string& iLine)
{
	int32_t firstNumber = 0;
	for (std::string::const_iterator i = iLine.begin(); i !=  iLine.end(); ++i)
	{
		if (std::isdigit(*i))
		{
			firstNumber = static_cast<int32_t>(*i - '0') * 10;
			break;
		}
	}

	int32_t lastNumber = 0;
	for (std::string::const_reverse_iterator i = iLine.rbegin(); i != iLine.rend(); ++i)
	{
		if (std::isdigit(*i))
		{
			lastNumber = static_cast<int32_t>(*i - '0');
			break;
		}
	}

	return firstNumber + lastNumber;
}


static int32_t SelectNumFromString(const std::string& iNumberStr)
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


int32_t ParseLine_Str(const std::string& iLine)
{
	ParsedLineData numDataForward;
	for (size_t i = 0; i < iLine.length(); ++i)
	{
		if (std::isdigit(iLine.at(i)))
		{
			numDataForward.dataPosition = i;
			numDataForward.data = static_cast<int32_t>(iLine.at(i) - '0');
			break;
		}
	}

	ParsedLineData strDataForward;
	for (const std::string& strNum : NumberStrs)
	{
		const size_t dataPos = iLine.find(strNum);
		if (dataPos != std::string::npos && !strDataForward.dataPosition.has_value() ||
			dataPos != std::string::npos && strDataForward.dataPosition > dataPos)
		{
			strDataForward.dataPosition = dataPos;
			strDataForward.data = SelectNumFromString(strNum);
		}
	}

	ParsedLineData numDataReverse;
	for (int32_t i = iLine.length() - 1; i >= 0; --i)
	{
		if (std::isdigit(iLine.at(i)))
		{
			numDataReverse.dataPosition = i;
			numDataReverse.data = static_cast<int32_t>(iLine.at(i) - '0');
			break;
		}
	}

	ParsedLineData strDataReverse;
	for (const std::string& strNum : NumberStrs)
	{
		const size_t dataPos = iLine.rfind(strNum);
		if (dataPos != std::string::npos && !strDataReverse.dataPosition.has_value() ||
			dataPos != std::string::npos && strDataReverse.dataPosition < dataPos)
		{
			strDataReverse.dataPosition = dataPos;
			strDataReverse.data = SelectNumFromString(strNum);
		}
	}

	// post-parse error check
	if (!numDataForward.dataPosition.has_value() && !strDataForward.dataPosition.has_value() ||
		!numDataReverse.dataPosition.has_value() && !strDataReverse.dataPosition.has_value())
	{
		std::cout << "bad row" << std::endl;
		return 0;
	}

	// first digit
	int32_t firstDigit = 0;
	if (numDataForward.dataPosition.has_value() && strDataForward.dataPosition.has_value())
	{
		if (numDataForward.dataPosition < strDataForward.dataPosition)
		{
			firstDigit = numDataForward.data;
		}
		else
		{
			firstDigit = strDataForward.data;
		}
	}
	else if (numDataForward.dataPosition.has_value() && !strDataForward.dataPosition.has_value())
	{
		firstDigit = numDataForward.data;
	}
	else if (!numDataForward.dataPosition.has_value() && strDataForward.dataPosition.has_value())
	{
		firstDigit = strDataForward.data;
	}
	else
	{
		std::cout << "No data found for first digit - bad row data";
	}

	// second digit
	int32_t secondDigit = 0;
	if (numDataReverse.dataPosition.has_value() && strDataReverse.dataPosition.has_value())
	{
		if (numDataReverse.dataPosition > strDataReverse.dataPosition)
		{
			secondDigit = numDataReverse.data;
		}
		else 
		{
			secondDigit = strDataReverse.data;
		}
	}
	else if (numDataReverse.dataPosition.has_value() && !strDataReverse.dataPosition.has_value())
	{
		secondDigit = numDataReverse.data;
	}
	else if (!numDataReverse.dataPosition.has_value() && strDataReverse.dataPosition.has_value())
	{
		secondDigit = strDataReverse.data;
	}
	else 
	{
		std::cout << "No data found for second digit - bad row data";
	}

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
