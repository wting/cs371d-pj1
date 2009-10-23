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
		Logger log(true,getpid());
		log.write(0,">>>parent");
		//log.write(0,boost::lexical_cast<string>(">>>parent, id = ") + boost::lexical_cast<string>(parent_ID));
		//cout << ">>>within parent" << endl;
		//cout << ">parent pID (fork result) = " << pID << endl;
		//cout << ">parent_pID = " << parent_ID << endl;
	} else if (pID == 0) {
		//cout << ">>>within child" << endl;
		dist::Node* N = new dist::Node();
		//cout << ">child, pID = " << getpid() << endl;
		//cout << ">child's parent_pID = " << parent_ID << endl;
		//N->log.write(0,"child process writing to log");
		delete N;
	} else {
		cerr << "Failed to fork" << endl;
		exit(1);
	}

    return 0;
}
