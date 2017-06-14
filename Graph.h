#pragma once

#include <fstream>
#include<iostream>
#include<string>
#include<regex>
#include"Node.h"


using namespace std;

class Graph
{
public:
	Graph();
	~Graph();

	void parseFile(string fileName);
	void clear();
	void updateConflicts();
	void prepareAnts();
	void coloring();
	void iteration();
	bool isColored();
	void recolor(int id);
	int getConflict(int id);
	int getConflictNodesNumber();
	void writeResult();

	string getFileName();
	int getChromaticNumber();
	int getAntsNumber();
	void setAntsNumber(int number);

private:

	int dead;
	
	string fileName;
	string fileNameResults;

	vector<Node> nodes;

	int chromaticNumber;
	int iterationNumber;
	int antsNumber;
	vector<int> ants;

};

