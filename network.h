#ifndef NETWORK_H
#define NETWORK_H

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
	//tcp::socket* p_sock;
	string host;
	int port;

	logger* log;

public:
	client(boost::asio::io_service& io, string h, string p, logger* l) :
		sock(io)
	//client(boost::asio::io_service& io, string h, string p, logger* l)
	{
		try {
			log = l;
			log->write(2,"network::client()");

			tcp::resolver resolver(io); //turns io into TCP endpoint
			tcp::resolver::query query(tcp::v4(), h, p); //constructing query
			tcp::resolver::iterator end_iterator = resolver.resolve(query); //turns query into list of endpoints
			tcp::resolver::iterator end;

			//creates socket and opens connection
			log->write(0,to_str("creating socket to ") + h + to_str(":") + p);
			//tcp::socket sock(io); //doesn't compile, doesn't socket need to be created after io's been modified?
			tcp::socket s(io);
			//p_sock = &tcp::socket sock(io);
			//tcp::socket sock(io);
			//socket = s(io);
			//tpc::socket sock(io);
			//socket = tcp::socket s(io);

			boost::system::error_code error = boost::asio::error::host_not_found;
			while (error && end_iterator != end) //iterate through all endpoints
			{
				s.close();
				s.connect(*end_iterator++, error);
			}
			if (error)
				throw boost::system::system_error(error);

			log->write(1,"sending: test");
			boost::asio::write(s,boost::asio::buffer("test",4));
			char ack[4];
			boost::asio::read(s,boost::asio::buffer(ack,4));
			log->write(1,to_str("response: ") + to_str(ack));
			//test();
		} catch (exception& e) {
			cerr << "Exception:" << e.what() << endl;
		}
	}

	~client() {
		log->write(2,"network::~client()");
		log = 0; //do not delete log, should be handled by caller
		//sock.close();
	}

	void send(string msg) {
		log->write(1,to_str("sending: ") + to_str(msg));
		boost::asio::write(sock,boost::asio::buffer(msg,msg.size()));
		response(msg.size());
	}

	void response(size_t len) {
		//string ack;
		char ack[4];
		boost::asio::read(sock,boost::asio::buffer(ack,len));
		log->write(1,to_str("response: ") + to_str(ack));
	}

	void test() {
		log->write(1,"sending: test");
		boost::asio::write(sock,boost::asio::buffer("test",4));
		char ack[4];
		boost::asio::read(sock,boost::asio::buffer(ack,4));
		log->write(1,to_str("response: ") + to_str(ack));
	}
};

class server {

};

} // end namespace dist

#endif // NETWORK_H
