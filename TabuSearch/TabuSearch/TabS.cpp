#include "pch.h"
#include "TabS.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <random>
#include <chrono>
#include<fstream>

using namespace std::chrono;
using namespace std;

TabS::TabS(int m_size, int **cities, int opt, int stop, int hood)
{
	this->cities = cities;
	this->m_size = m_size;
	cost = 0;
	divLvl = 0;
	choice = hood;
	this->opt = opt;
	theBestSolutionCost = INT32_MAX;
	timeCounterStop = 0;
	sec = stop;
	dyw = true;
}

int TabS::pathCostList(vector<int> xpath) {
	cost = 0;
	for (int i = 0; i < xpath.size() - 1; i++) {
		cost = cost + cities[xpath.at(i)][xpath.at(i + 1)];
	}

	cost = cost + cities[xpath.at(xpath.size() - 1)][xpath.at(0)];
	return cost;
}

void TabS::tabuSearch()
{
	//cout << "Rozmiar macierzy: \n" << m_size;

	tabuList = new int*[m_size];

	for (int i = 0; i < m_size; i++)
	{
		tabuList[i] = new int[m_size];
		path.push_back(i);
		for (int j = 0; j < m_size; j++)
		{
			tabuList[i][j] = 0;
		}

	}

	//std::copy(path.begin(), path.end(),
	//	std::ostream_iterator<int>(std::cout, " "));

	time = m_size;

	maxDivLvl = m_size * 2;


	compute();
	printPath();
}

void TabS::compute()
{

	random_shuffle(begin(path), end(path));

//	cout << "\nShuffled vector: ";
//	std::copy(path.begin(), path.end(),
//		std::ostream_iterator<int>(std::cout, " "));

	vector<int> temporaryNewSol;
	theBestSolutionCost = pathCostList(path);
	vector<int> BestSolution;

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	duration<double> time_span;
	//ofstream zapis("dane.txt", ios_base::app);
	while (time_span.count() <= sec) {

		int city1 = 0; 
		int city2 = 0;
		int bestCost = INT32_MAX;
		for (size_t j = 1; j < m_size; j++)
		{
			for (size_t k = 2; k < m_size; k++)
			{
				if (j != k)
				{
					temporaryNewSol.clear();
					for (size_t m = 0; m < path.size(); m++)
					{
						temporaryNewSol.push_back(path.at(m));
					}

					if (choice == 1)
					{
						swap(temporaryNewSol, j, k); 
					}
					if (choice==2)
					{
						insert(temporaryNewSol, j, k); 
					}
					if (choice==3)
					{
						invert(temporaryNewSol, j, k); 
					}

					int newCost = pathCostList(temporaryNewSol);			 

					if (newCost < bestCost && tabuList[j][k] == 0)
					{															
						BestSolution.clear();									
						for (size_t m = 0; m < path.size(); m++)
						{
							BestSolution.push_back(temporaryNewSol.at(m));
						}
						city1 = j; 
						city2 = k;
						bestCost = newCost;
					}
				}
			}
		}

		if (city1 != 0)
		{
			decrease(); 
			addTabu(city1, city2); 
		}
		if (theBestSolutionCost > bestCost)
		{ 
			theBestSolutionCost = bestCost;
			
			float er = ((abs(opt - bestCost) / (float)opt) * 100);
			
		//	zapis << bestCost<<"\t";
		//	zapis << time_span.count()<<"\t";
		//	zapis << er << "\n";

			std::cout << "\nAlgorithm time stand: " << time_span.count();
			cout << "\t best cost: ";
			printBestCost();
			cout << "\t relative error: " << er << "%";

			
			theBestSolutionPath.clear();
			for (int m = 0; m < BestSolution.size(); m++)
			{
				theBestSolutionPath.push_back(BestSolution.at(m)); 
			}
		}

		if (choice == 1)
		{
			swap(path, city1, city2); 
		}
		if (choice==2)
		{
			insert(path, city1, city2); 
		}
		if (choice==3)
		{
			invert(path, city1, city2); 
		}

		if(dyw==true)
			diversification(bestCost, theBestSolutionPath); 

		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		time_span = duration_cast<duration<double>>(t2 - t1);
	}
//	zapis.close();
}

void TabS::swap(vector<int>& xpath, int i, int j) {
	int tmp = xpath.at(i);                                                  
	xpath.at(i) = xpath.at(j);
	xpath.at(j) = tmp;
}

void TabS::insert(vector<int>& xpath, int i, int j)
{
	int tmp = xpath.at(j);
	xpath.erase(xpath.begin() + j);
	xpath.insert(xpath.begin() + i, tmp);
}

void TabS::invert(std::vector<int>& xpath, int i, int j)
{
	vector<int> temporary_1;
	vector<int> temporaryReverse;

	if (i < j) {
		for (int h = 0; h < i; h++) {
			temporary_1.push_back(xpath.at(h));
		}
		for (int h = i; h < j; h++) {
			temporaryReverse.push_back(xpath.at(h));
		}reverse(temporaryReverse.begin(), temporaryReverse.end());
		for (int h = 0; h < temporaryReverse.size(); h++) {
			temporary_1.push_back(temporaryReverse.at(h));
		}
		for (int h = j; h < xpath.size(); h++) {
			temporary_1.push_back(xpath.at(h));
		}
	}
	if (i > j) {
		for (int h = 0; h < j; h++) {
			temporary_1.push_back(xpath.at(h));
		}
		for (int h = j; h < i; h++) {
			temporaryReverse.push_back(xpath.at(h));
		}reverse(temporaryReverse.begin(), temporaryReverse.end());
		for (int h = 0; h < temporaryReverse.size(); h++) {
			temporary_1.push_back(temporaryReverse.at(h));
		}
		for (int h = i; h < xpath.size(); h++) {
			temporary_1.push_back(xpath.at(h));
		}
	}

	xpath.clear();
	for (int h = 0; h < temporary_1.size(); h++)
	{
		xpath.push_back(temporary_1.at(h));
	}
}



void TabS::diversification(int bestCost, vector<int> bestBestSol) {
	if (theBestSolutionCost <= bestCost)
	{ 
		divLvl++;
	}
	else
	{
		divLvl = 0;
	}

	if (divLvl > maxDivLvl)
	{ 
		vector<int> tmp;
		for (int n = 0; n < path.size(); n++)
		{ 
			tmp.push_back(path.at(n));
		}
		for (int m = 0; m < m_size; m++)
		{
			random_shuffle(begin(tmp), end(tmp));

			if (pathCostList(path) > pathCostList(tmp))
			{ 
				path.clear(); 
				for (int n = 0; n < tmp.size(); n++)                                     
				{																		 
					path.push_back(tmp.at(n));
				}
				if (theBestSolutionCost > pathCostList(path))
				{ 
					bestBestSol.clear();
					for (int n = 0; n < path.size(); n++)
					{
						bestBestSol.push_back(path.at(n));
					}
				}
			}
		}
		for (int m = 0; m < m_size; m++)
		{ 
			for (int n = 0; n < m_size; n++)
			{
				tabuList[m][n] = 0;
			}
		}
		divLvl = 0;
	}
}

void TabS::addTabu(int city1, int city2) {
	tabuList[city1][city2] += time;                                          
	tabuList[city2][city1] += time;
}

void TabS::decrease() {                                              
	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++) {
			if (tabuList[i][j] > 0) {

				tabuList[i][j]--;

			}
		}
	}
}

void TabS::printBestCost()
{
	cout << theBestSolutionCost;
}

void TabS::printPath()
{
	cout << "\n\nThe best cost --> " << pathCostList(theBestSolutionPath) << "\n\nThe best path found --> ";

	for (int i = 0; i < theBestSolutionPath.size(); i++) {
		cout << theBestSolutionPath.at(i) << " ";
	}
	cout << theBestSolutionPath.at(0) << "\n";

	theBestSolutionPath.clear();
	path.clear();
}

TabS::~TabS()
{
}
