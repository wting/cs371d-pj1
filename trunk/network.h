#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "aux.h"
#include "logger.h"

using namespace std;
using aux::to_str;
using boost::asio::ip::tcp;

namespace network {

class client :
	public boost::enable_shared_from_this<client>
{
	boost::asio::io_service io;
	tcp::socket sock;
	string host;
	int port;

	logger* log;

public:
	client(boost::asio::io_service& io, string h, int p, logger* l) :
		sock(io)
	{
		try {
			log = l;
			log->write(2,"network::client()");

			tcp::resolver resolver(io); //turns io into TCP endpoint
			tcp::resolver::query query(tcp::v4(), h, to_str(p)); //constructing query
			tcp::resolver::iterator end_iterator = resolver.resolve(query); //turns query into list of endpoints
			tcp::resolver::iterator end;

			//creates socket and opens connection
			log->write(0,"creating socket");
			tcp::socket sock(io); //doesn't compile, doesn't socket need to be created after io's been modified?
			boost::system::error_code error = boost::asio::error::host_not_found;
			while (error && end_iterator != end) //iterate through all endpoints
			{
				sock.close();
				sock.connect(*end_iterator++, error);
			}
			if (error)
				throw boost::system::system_error(error);
		} catch (exception& e) {
			cerr << "Exception:" << e.what() << endl;
		}
	}

	~client() {
		log->write(2,"network::~client()");
		log = 0; //do not delete log as it should handled by calling parent function
		sock.close();
	}

	void send(string msg) {
		log->write(1,to_str("sending: ") + to_str(msg));
		boost::asio::write(sock,boost::asio::buffer(msg,msg.size()));
	}

	/*void response() {
		//string ack;
		boost::asio::read(sock,boost::asio::buffer(ack,ack.size()));
	}*/
};

class server {

};

} // end namespace dist

#endif // NETWORK_H
