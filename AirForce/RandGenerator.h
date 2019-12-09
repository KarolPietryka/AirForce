#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class RandGenerator
{
public:
	RandGenerator();
	unsigned rand();
	unsigned getKernel();
	~RandGenerator();
private:
	//ofstream randNumFile_Write;
	//ifstream randNumFile_Read;
	unsigned kernel;
	double M;
	int A;
	int Q;
	int R;
};

