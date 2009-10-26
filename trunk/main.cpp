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

#include "aux.h"
#include "logger.h"
#include "node.h"
#include "network.h"

using namespace std;
using namespace aux;

volatile bool child_exit = false;

void sig_child(int sig) {
	//cout << "caught signal " << sig << endl;
	child_exit = true;
}

int main(int argc, char* argv[]) {
	(void) signal(SIGINT,sig_child);

	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <port>" << endl;
		return 1;
	}

	pid_t parent_ID = getpid();
	pid_t pID = fork();
	if (pID > 0) {
		logger* log = new logger(0,parent_ID);
		log->write(5,"parent process beg");
		log->write(0,to_str("forked child (pid = ") + to_str(pID) + to_str(")"));

		{
			log->write(0,"creating network client to server");
			network::client cl("localhost",argv[1],log);
			string line;
			log->write(2,"beginning input block");
			while (true) {
				///\TODO:check if child process is dead by response of sending command to network socket
				if (child_exit)
					exit(0);

				cout << endl;
				cout << "input: ";
				getline(cin,line);

				if (cin.eof() || line.compare("exit") == 0)
					break;
				log->write(4,to_str("sending input to child process = ") + to_str(line));
				cl.send(line);
			}
		}

		log->write(4,"request child process to terminate");
		//send command to network socket
		kill(pID,SIGINT);
		//wait 3 sec, check for existence of child?  send kill command
		waitpid(pID,0,0);

		log->write(5,"parent process end");
		delete log;
	} else if (pID == 0) {
		logger log(0,getpid());
		log.write(5,"child process beg");
		dist::node* n = new dist::node(&log);

		delete n;
		while (!child_exit) {;}
		log.write(5,"child process end");
	} else {
		cerr << "Failed to fork" << endl;
		exit(1);
	}

    return 0;
}
