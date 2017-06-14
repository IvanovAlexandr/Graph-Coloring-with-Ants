#include "Graph.h"



Graph::Graph()
{
	srand(time(0));
	clear();
}


Graph::~Graph()
{
}

void Graph::parseFile(string _fileName)
{
	clear();
	fileName = _fileName;
	fileNameResults = fileName.substr(0, fileName.length() - 4) + ".log";
	
	int first = fileName.find('.') + 1;
	
	chromaticNumber = stoi(fileName.substr(first, fileName.find('.', first) - first));

	ifstream fin("../Graphs/" + fileName);
	string line;
	if(!fin.is_open()) 
		cout << "Not found!\n"; 
	else
	{
		while (getline(fin, line)) {
			if (line[0] == 'p') {
				regex e("[[:digit:]]+");
				std::smatch m;
				regex_search(line, m, e); 
				string buff = "";
				for (auto x : m) buff += x;
				int nodesNumber = stoi(buff);
				//line = m.suffix().str();
				cout << "Start color: " << endl;
				
				for (int i = 0; i < nodesNumber; i++) {
					int color = rand() % chromaticNumber;
					nodes.push_back(Node(color));
					cout << "\tNode " << i+1 << " color " << color << endl;
				}
			}
			if (line[0] == 'e') {
				regex e("[[:digit:]]+");
				std::smatch m;
				regex_search(line, m, e);
				string buff = "";
				for (auto x : m) buff += x;
				int node1 = stoi(buff) - 1;
				line = m.suffix().str();
				regex_search(line, m, e);
				buff = "";
				for (auto x : m) buff += x;
				int node2 = stoi(buff) - 1;

				nodes[node1].connectedWith.push_back(node2);
				nodes[node2].connectedWith.push_back(node1);				
			}
		}
		fin.close();
	}
	antsNumber = nodes.size() / 3;
}

void Graph::clear()
{
	nodes.clear();
	chromaticNumber = 0;
	iterationNumber = 0;
	antsNumber = 0;
	ants.clear();
}

void Graph::updateConflicts()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		nodes[i].conflictsNumber = 0;
		
		for each (int neighbor in nodes[i].connectedWith) {
			if (nodes[neighbor].colorNumber == nodes[i].colorNumber) {
				nodes[i].conflictsNumber++;
			}
		}
	}
}

void Graph::prepareAnts()
{
	cout << "Prepare" << endl;
	updateConflicts();
	ants.clear();
	for (int i = 0; i < antsNumber; i++) {
		int n = rand() % nodes.size();
		ants.push_back(n);
		cout << "Ant " << i+1 << " in node " << n+1 << endl;
	}
	iterationNumber = 0;
}

void Graph::coloring()
{
	prepareAnts();

	do {
		iteration();
	} while(!isColored());
	cout << "Graph is colored" << endl;
	cout << "Iterations = " << iterationNumber << endl;
	writeResult();
	cout << "finish color: " << endl;

	for (int i = 0; i < nodes.size(); i++) {
		cout << "\tNode " << i+1 << " color " << nodes[i].colorNumber << endl;
	}

	cout << "\nResults in " << fileNameResults << endl;


}

void Graph::iteration()
{
	cout << "Iteration " << iterationNumber << endl;

	for (int i = 0; i < ants.size(); i++) {
		if (nodes[ants[i]].connectedWith.size() == 0)
			continue;

		int nodeMax = nodes[ants[i]].connectedWith[0];
		int confsoverall = 0;

		for each (int neighbor in nodes[ants[i]].connectedWith) {
			confsoverall += nodes[neighbor].conflictsNumber;
			if (nodes[nodeMax].conflictsNumber < nodes[neighbor].conflictsNumber)
				nodeMax = neighbor;
		}

		int maxconf = nodes[nodeMax].conflictsNumber;
		int p = 0;
		double avgY = 4.8 * confsoverall / (nodes.size() * nodes.size());
		double avgX = 1. * maxconf;
		p = exp(-3.2 * ((5 * iterationNumber + 1) * avgY / avgX));

		if (rand() % 100 < p)
			ants[i] = nodeMax;
		else
			ants[i] = nodes[ants[i]].connectedWith[rand() % nodes[ants[i]].connectedWith.size()];

		cout << "Ant " << i+1 << " moves from node " << i+1 << " to node " << ants[i]+1 << endl;
		recolor(ants[i]);
	}
	cout << "Conflict nodes = " << getConflictNodesNumber() << endl;
	iterationNumber++;
}

bool Graph::isColored()
{
	if (getConflictNodesNumber() > 0)
		return false;
	return true;
}

void Graph::recolor(int id)
{
	int currentColor = nodes[id].colorNumber;
	int min = nodes[id].conflictsNumber;
	vector<int> minColors = vector<int>();
	for (int color = 0; color < chromaticNumber; color++) {
		nodes[id].colorNumber = color;
		int conflicts = getConflict(id);
		if (conflicts < min) {
			min = conflicts;
			minColors.clear();
			minColors.push_back(color);
		} else if (conflicts == min) {
			minColors.push_back(color);
		}
	}
	if (minColors.size() > 0)
		nodes[id].colorNumber = minColors[rand() % minColors.size()];

	if (currentColor != nodes[id].colorNumber) {
		updateConflicts();
		cout << "\tRecolor from " << currentColor << " to " << nodes[id].colorNumber << endl;
	}
}

int Graph::getConflict(int id)
{
	Node node = nodes[id];
	int conflict = 0;
	for each (int n in node.connectedWith) {
		if (node.colorNumber == nodes[n].colorNumber)
			conflict++;
	}
	return conflict;
}

int Graph::getConflictNodesNumber()
{
	int conflict = 0;
	for each (Node node in nodes) {
		if (node.conflictsNumber != 0)
			conflict++;
	}
	return conflict;
}

void Graph::writeResult()
{
	ofstream fout("../Graphs/" + fileNameResults);
	fout << "Colored graph for file" << fileName << endl;
	fout << "Iterations = " << iterationNumber << endl;
	for (int i = 0; i < nodes.size(); i++) {
		fout << "Node " << i+1 << " color = " << nodes[i].colorNumber << endl;
	}
	fout.close();
}

string Graph::getFileName()
{
	return fileName;
}

int Graph::getChromaticNumber()
{
	return chromaticNumber;
}

int Graph::getAntsNumber()
{
	return antsNumber;
}

void Graph::setAntsNumber(int number)
{
	antsNumber = number;
}





