/*
    @file Node.h
    @brief Implement of graph node
    @author Alexandr Ivanov (alexandr.ivanov.1995@gmail.com)
*/

#ifndef NODE_H
#define NODE_H

#include <vector>

class Node
{
public:
	Node();
	Node(int color);
	~Node();

	std::vector<int> connectedWith;
	int colorNumber;
	int conflictsNumber;

};

#endif //NODE_H