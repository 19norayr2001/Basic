#include <iostream>
#include <exception>
#include <string>
#include "UnitTests.h"
#include "../File Manager/FileManager.h"
void Testing::FileMenegerEmulatorTesting()
{
	FileManager m;
	std::string s;
	while (getline(std::cin, s))
	{
		try
		{
			m.Command(s);
			std::cout << m << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}