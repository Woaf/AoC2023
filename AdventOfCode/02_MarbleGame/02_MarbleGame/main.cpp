#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


int main()
{
	std::ifstream rawDataFile("rawdata.txt");
	if (!rawDataFile.is_open())
	{
		std::cout << "No input file found..." << std::endl;
		return -1;
	}



	return 0;
}