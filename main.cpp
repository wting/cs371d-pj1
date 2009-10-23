/**
	\file main.cpp
	\brief CS 371D Project - Playlist Editing

	\author HanPing Ting
	\author Will Warner
*/

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "Aux.h"
#include "Logger.h"
#include "Node.h"

using namespace std;
using namespace aux;

volatile bool child_exit = false;

void sig_child(int sig) {
	//cout << "caught signal " << sig << endl;
	child_exit = true;
}

int main(int argc, char* argv[]) {
	(void) signal(SIGINT,sig_child);

	pid_t parent_ID = getpid();
	pid_t pID = fork();
	if (pID > 0) {
		Logger log(0,parent_ID);
		log.write(5,"parent process beg");
		log.write(0,to_str("forked child (pid = ") + to_str(pID) + to_str(")"));

		string input;
		while (true) {
			if (child_exit)
				exit(0);

			getline(cin,input);
			if (cin.eof() || input.compare("exit") == 0)
				break;
			log.write(4,to_str("sending input to child process = ") + to_str(input));
			///\TODO:check if child process is dead by response of sending command to network socket
		}

		log.write(4,"request child process to terminate");
		//send command to network socket
		kill(pID,SIGINT);
		//wait 3 sec, check for existence of child?  send kill command
		waitpid(pID,0,0);
		log.write(5,"parent process end");
	} else if (pID == 0) {
		Logger log(0,getpid());
		log.write(5,"child process beg");
		dist::Node* N = new dist::Node(&log);

		delete N;

		//while (!child_exit) {;}
		log.write(5,"child process end");
	} else {
		cerr << "Failed to fork" << endl;
		exit(1);
	}

    return 0;
}
