#include "pch.h"
#include "ReadFile.h"
#include <iostream>
#include <fstream>
#include<string>


ReadFile::ReadFile()
{
}

int **ReadFile::openFile(int &m_size,int &opt, std::string fileName)
{
	int **cities;
	std::ifstream in(fileName);
	std::string buf;

	if (!in) {
		std::cout << "nie mozna otworzyc pliku.\n";
		return 0;
	}
	in >> opt;
	in >> m_size;
	in >> buf;
	if (buf == "LOWER_DIAG_ROW") {
		cities = new int*[m_size];
		int weightEdge;
		for (int v1 = 0; v1 < m_size; v1++) {
			cities[v1] = new int[m_size];
			for (int v2 = 0; v2 <= v1; v2++) {
				in >> weightEdge;
				if (weightEdge >= 0) {
					cities[v1][v2]=weightEdge;
					cities[v2][v1]=weightEdge;
					if(v1==v2)
						cities[v1][v2]=-1;
				}
			}
		}
	}
	else {
		cities = new int*[m_size];

		for (int i = 0; i < m_size; i++) {

			cities[i] = new int[m_size];

			for (int j = 0; j < m_size; j++) {

				in >> cities[i][j];

				if (j == i)
					cities[i][j] = -1;
			}
		}
	}
	in.close();
	return cities;
}


ReadFile::~ReadFile()
{
}
