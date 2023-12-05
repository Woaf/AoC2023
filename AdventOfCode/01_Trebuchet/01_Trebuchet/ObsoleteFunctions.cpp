#if 0


int32_t ParseLine(const std::string& iLine)
{
	int32_t firstNumber = 0;
	for (std::string::const_iterator i = iLine.begin(); i != iLine.end(); ++i)
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


#endif
