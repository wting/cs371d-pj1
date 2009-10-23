/**
	\file main.cpp
	\brief CS 371D Project - Playlist Editing

	\author HanPing Ting
	\author Will Warner
*/

#include <iostream>
#include <fstream>
#include <string>
#include <boost/lexical_cast.hpp>
#include "Logger.h"
#include "Node.h"

using namespace std;

int main(int argc, char* argv[]) {

	/*string line;
	while (true) {
		getline(cin,line);
		if (cin.eof())
			break;
		N->parse(line);
	}
	*/

	pid_t parent_ID = getpid();
	pid_t pID = fork();
	if (pID > 0) {
		Logger log(0,parent_ID);
		log.write(5,">>>parent process");
		log.write(0,boost::lexical_cast<string>("forked child (pid = ") + boost::lexical_cast<string>(pID) + boost::lexical_cast<string>(")"));
	} else if (pID == 0) {
		Logger log(0,getpid());
		log.write(5,">>>child process");
		dist::Node* N = new dist::Node(&log);

		delete N;
	} else {
		cerr << "Failed to fork" << endl;
		exit(1);
	}

    return 0;
}
