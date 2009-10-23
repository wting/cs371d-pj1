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
#include "Aux.h"
#include "Logger.h"
#include "Node.h"

using namespace std;
using namespace aux;

int main(int argc, char* argv[]) {

	pid_t parent_ID = getpid();
	pid_t pID = fork();
	if (pID > 0) {
		Logger log(0,parent_ID);
		log.write(5,">>>parent process");
		log.write(0,boost::lexical_cast<string>("forked child (pid = ") + boost::lexical_cast<string>(pID) + boost::lexical_cast<string>(")"));
		log.write(0,to_str("forked child (pid = ") + to_str(pID) + to_str(")"));

		string input;
		while (true) {
			getline(cin,input);
			if (cin.eof())
				break;
			log.write(5,input);
			//N->parse(line);
		}
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
