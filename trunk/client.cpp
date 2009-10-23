
#include <iostream>
#include <boost/asio.hpp>
#include "aux.h"
#include "logger.h"
#include "network.h"

using namespace std;

int main() {
	logger* log = new logger(0,getpid());

	{
	boost::asio::io_service io;
	network::client cl(io,aux::to_str("localhost"),10000,log);
	} // to force cl to destruct w/o destroying log

	delete log;
	return 0;
}
