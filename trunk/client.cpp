
#include <iostream>
#include <boost/asio.hpp>
#include "aux.h"
#include "logger.h"
#include "network.h"

using namespace std;

int main(int argc, char* argv[]) {
	logger* log = new logger(0,getpid());

	boost::asio::io_service io;
	if (argc != 3) {
		cerr << "Usage: blocking_tcp_echo_client <host> <port>" << endl;
		return 1;
	}

	{
		network::client cl(io,argv[1],argv[2],log);
		string line;
		while (true) {
			cout << "input: ";
			getline(cin,line);
			if (line.compare("exit") == 0 || cin.eof())
				break;
			cl.send(line);
		}
		cout << endl;
	} // force ~client() to prevent destroying log

	delete log;
	return 0;
}
