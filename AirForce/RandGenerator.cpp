#include "stdafx.h"
#include "RandGenerator.h"


RandGenerator::RandGenerator()
{
	ifstream randNumFile_Read("Rand.txt");
	if (randNumFile_Read.is_open())
	{
		string line;
		//ifstream randNumFile_Read("Rand.txt");
		while (getline(randNumFile_Read, line))
		{
			kernel = stoi(line);
		}
		randNumFile_Read.close();
	}
	M = 2147483647.0;
	A = 16807;
	Q = 127773;
	R = 2836;
}
unsigned RandGenerator::rand()
{
	int h = kernel / Q;
	kernel = A * (kernel - Q*h) - R*h;
	if (kernel < 0)
	{
		kernel = kernel + static_cast<int>(M);
	}
	ofstream randNumFile_Write("Rand.txt");
	if (randNumFile_Write.is_open())
	{
		randNumFile_Write << (kernel % 293831959);  // TODO why number greater then 4 294 967 295 in rand.txt is out of Range exception in constructor?
		randNumFile_Write.close();
	}
	return kernel;
}

RandGenerator::~RandGenerator()
{
}
//4293831959
//4294967294
