/**
	\file main.cpp
	\brief CS 371D Project - Playlist Editing

	\author HanPing Ting
	\author Will Warner
*/

#include <iostream>
#include <fstream>
#include <string>
#include "Node.h"

using namespace std;

int main(int argc, char* argv[]) {
	dist::Node* N = new dist::Node();

	string line;
	while (true) {
		getline(cin,line);
		if (cin.eof())
			break;
		N->parse(line);
	}

	delete N;
    return 0;
}
