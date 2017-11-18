/*
    @file graph.h
    @brief Implement of graph
    @author Alexandr Ivanov (alexandr.ivanov.1995@gmail.com)
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include<iostream>
#include<string>
#include<regex>
#include"Node.h"


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

	std::string getFileName();
	int getChromaticNumber();
	int getAntsNumber();
	void setAntsNumber(int number);

private:

	int dead;
	
	std::string fileName;
	std::string fileNameResults;

	std::vector<Node> nodes;

	int chromaticNumber;
	int iterationNumber;
	int antsNumber;
	std::vector<int> ants;

};

#endif //GRAPH_H