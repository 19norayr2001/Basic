#include <iostream>
#include <string>
#include "UnitTests.h"
#include "../File Manager/FileManager.h"
void Testing::FileMenegerEmulatorTesting()
{
	FileManager m;
	std::string s;
	while (getline(std::cin, s))
	{
		m.Command(s);
	}
}