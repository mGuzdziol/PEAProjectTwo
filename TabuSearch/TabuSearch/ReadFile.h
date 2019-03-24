#pragma once
#include <vector>

class ReadFile
{
	
public:
	ReadFile();

	int **openFile(int &cities,int &opt, std::string fileName);

	~ReadFile();
};
