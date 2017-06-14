#pragma once
#include <vector>

using namespace std;

class Node
{
public:
	Node();
	Node(int color);
	~Node();

	vector<int> connectedWith;
	int colorNumber;
	int conflictsNumber;

};

