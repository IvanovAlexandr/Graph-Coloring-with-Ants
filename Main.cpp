/*
    @file Main.cpp
    @brief Graph coloring test
    @author Alexandr Ivanov (alexandr.ivanov.1995@gmail.com)
*/

#include <sstream>
#include <Windows.h>
#include"Graph.h"

using namespace std;

string selectFile() {
	WIN32_FIND_DATAW wfd;
	HANDLE const hFind = FindFirstFileW(L"../Graphs/*.col", &wfd);

	string fileName = "";

	if (INVALID_HANDLE_VALUE != hFind)
	{
		int i = 0;
		vector<string> vec;
		do
		{
			i++;
			wstring pszFileName = &wfd.cFileName[0];
			vec.push_back(string(pszFileName.begin(), pszFileName.end()));
			cout << i << ") " << vec.back() << endl;
			if (i == 9) {
				i = 0;
				int option;
				cout << "0) next page >>" << endl;
				cout << "Input option: ";
				while (!(cin >> option) || (cin.peek() != '\n'))
				{
					cin.clear();
					while (cin.get() != '\n');
					cout << "Error!" << endl;
				}
				if (option != 0) {
					fileName = vec[option - 1];
					FindClose(hFind);
					return fileName;
				} 
				vec.clear();
				
			}
		} while (NULL != FindNextFileW(hFind, &wfd));

		int option;
		cout << "Input option: ";
		while (!(cin >> option) || (cin.peek() != '\n'))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Error!" << endl;
		}
		if (option != 0) {
			fileName = vec[option - 1];
		}

		FindClose(hFind);
	}

	return fileName;

}

int selectAntsNumber() {
	cout << "\nSelect ants number: " << endl;
	int n;
	while (!(cin >> n) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Error!" << endl;
	}
	return n;
}

void menu(Graph graph) {
	while (true)
	{
		cout << "\n\n\tParams" << endl;
		cout << "File name : " << graph.getFileName() << endl;
		cout << "Chromatic number : " << graph.getChromaticNumber() << endl;
		cout << "Ants number : " << graph.getAntsNumber() << endl;

		int option;
		
		cout << "\tMenu" << endl;
		cout << "1) Open file" << endl;
		cout << "2) Number of ants" << endl;
		cout << "3) Coloring" << endl;
		cout << "0) End" << endl;
		cin >> option;
		switch (option)
		{
			case 1: {
				graph.parseFile(selectFile());
				break;
			}
			case 2: {
				graph.setAntsNumber(selectAntsNumber());
				break;
			}
			case 3: {
				graph.coloring();
				break;
			}
			case 0: {
				return;
			}
			default: {
				cout << "Wrong input! Try again!" << endl;
				break;
			}
		}
	}
	
}


int main()
{
	Graph graph = Graph();
	//graph.coloring();

	menu(graph);

	system("pause");
	return 0;
}


