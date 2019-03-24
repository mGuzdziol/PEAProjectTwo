#pragma once
#include <vector>

class TabS
{
	int **cities;
	int m_size;
	int **tabuList;
	std::vector<int> path;
	int time;
	int maxDivLvl;
	std::vector<int> theBestSolutionPath;
	int cost;
	int choice;
	int divLvl;
	int theBestSolutionCost;
	long timeCounterStart, timeOfFoundTheBestPath, FinalTime;
	long timeCounterStop = 0;
	float sec;
	int opt;
	bool dyw;

public:
	TabS(int m_size, int **cities, int opt,int stop,int hood);
	void tabuSearch();
	void compute();
	void printBestCost();
	int pathCostList(std::vector<int> xpath);
	void decrease();
	void swap(std::vector<int>& xpath, int i, int j);
	void insert(std::vector<int>& xpath, int i, int j);
	void invert(std::vector<int>& xpath, int i, int j);
	void addTabu(int city1, int city2);
	void diversification(int bestCost, std::vector<int> bestBestSol);
	void printPath();
	~TabS();
};

