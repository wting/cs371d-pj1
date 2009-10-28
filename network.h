#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/lexical_cast.hpp>
#include "aux.h"
#include "logger.h"
#include "node.h"

using namespace std;
using aux::to_str;
using boost::asio::ip::tcp;

namespace network {

class client :
	//keep alive as long as something is pointing to this
	public boost::enable_shared_from_this<client> {
	boost::asio::io_service io;
	string host;
	string port;
	size_t buffer_length;

	logger* log;

public:
	client(string h, string p, logger* l) {
		log = l;
		log->write(2,"network::client()");
		host = h;
		port = p;
	}

	~client() {
		log->write(2,"network::~client()");
		log = 0; //do not delete log, should be handled by caller
	}

	string send(string msg) {
		try {
			log->write(4,to_str("send: ") + msg);

			tcp::resolver resolver(io); //turns io into TCP endpoint
			tcp::resolver::query query(tcp::v4(), host, port); //constructing query
			tcp::resolver::iterator end_iterator = resolver.resolve(query); //turns query into list of endpoints
			tcp::resolver::iterator end;

			//creates socket and opens connection
			log->write(0,to_str("creating socket to ") + host + to_str(":") + port);
			tcp::socket s(io);

			boost::system::error_code error = boost::asio::error::host_not_found;
			while (error && end_iterator != end) //iterate through all endpoints
			{
				s.close();
				s.connect(*end_iterator++, error);
			}
			if (error)
				throw boost::system::system_error(error);

			char ack[1024];
			string reply;

			log->write(3,to_str("sending:  ") + msg);
			log->write(0,"write buffer");
			boost::asio::write(s,boost::asio::buffer(msg,msg.size()));
			log->write(0,"read  buffer");
			boost::asio::read(s,boost::asio::buffer(ack,msg.size()));
			reply = to_str(ack).substr(0,msg.size());
			log->write(3,to_str("response: ") + to_str(reply));

			s.close();
			log->write(4,to_str("send end"));
			return to_str(reply);
		} catch (exception& e) {
			cerr << "Exception:" << e.what() << endl;
		}

		return NULL;
	}
};

class session {
public:
	session(boost::asio::io_service& io_service) : socket_(io_service) { }

	tcp::socket& socket() { return socket_; }

	void start() {
		socket_.async_read_some(boost::asio::buffer(data_, max_length),
				boost::bind(&session::handle_read, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}

	void handle_read(const boost::system::error_code& error, size_t bytes_transferred) {
		if (!error) {
			boost::asio::async_write(socket_,
					boost::asio::buffer(data_, bytes_transferred),
					boost::bind(&session::handle_write, this,
					boost::asio::placeholders::error));
		} else { delete this; }
	}

	void handle_write(const boost::system::error_code& error) {
		if (!error) {
			socket_.async_read_some(boost::asio::buffer(data_, max_length),
					boost::bind(&session::handle_read, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
		} else { delete this; }
	}

private:
	tcp::socket socket_;
	enum { max_length = 1024 };
	char data_[max_length];
};

class server {
	boost::asio::io_service& io_service_;
	tcp::acceptor acceptor_;

	short int port;
	dist::node* node;
	logger* log;

public:
	server(boost::asio::io_service& io_service, string p, logger* l) :
		//initializes io, acceptor to listen on port argument
		io_service_(io_service), acceptor_(io_service, tcp::endpoint(tcp::v4(), boost::lexical_cast<short int>(p))) {
			log = l;
			log->write(5,"network::server()");
			port = boost::lexical_cast<short int>(p);

			node = new dist::node();

			//creates new session for use with async
			session* new_session = new session(io_service_);

			//initiates async_accept operation to wait for new connections
			acceptor_.async_accept(new_session->socket(), boost::bind(&server::handle_accept, this, new_session, boost::asio::placeholders::error));
	}

	~server() {
		log->write(5,"network::~server()");
		delete node;
	}

	//event handler called by async_accept, services client request and then initiates next async_accept operation
	void handle_accept(session* new_session, const boost::system::error_code& error) {
		if (!error) {
			new_session->start();
			new_session = new session(io_service_);
			acceptor_.async_accept(new_session->socket(), boost::bind(&server::handle_accept, this, new_session, boost::asio::placeholders::error));
		} else { delete new_session; }
	}
};

} // end namespace network

#endif // NETWORK_H
