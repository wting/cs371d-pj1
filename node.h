#ifndef NODE_H
#define NODE_H

#include <stdexcept>
#include <string>
#include <boost/unordered_map.hpp>
#include <boost/asio.hpp>

#include "aux.h"
#include "logger.h"
#include "network.h"

using namespace std;
using aux::to_str;

namespace dist {

class node {
	boost::unordered_map<string, string> song_list;
	boost::unordered_map<string, string> node_list;

	boost::asio::io_service io;
	short int port;
	string status;

	logger* log;

public:
	node(boost::asio::io_service& io, string p, logger* l) {
		log = l;
		log->write(2,"dist::node()");
		log->write(3,to_str("creating server on port ") + p);
		port = boost::lexical_cast<short int>(p);
		network::server s(io, port);

		log->write(3,"running server");
		io.run();
	}

	~node() {
		log->write(2,"dist::~node()");
	}

	void parse(string input) {
		//if (validate_input(input))

		//log.write(5,"input: " + input);
	}

	///\TODO:finish
	bool validate_input(string input) {
		return true;
	}

	//song related functions
	void add(string song, string url) {
		if (song_list.find(song) == song_list.end())
			song_list[song] = url;
		else
			throw runtime_error("add failed, song already exists.");
	}

	void del(string song) {
		/*if (song_list.find(song) == song_list.end())
			throw runtime_error("delete failed, song does not exist.");
		else
			song_list.erase(song);*/
		song_list.erase(song);
	}

	void edit(string song, string url) {
		if (song_list.find(song) == song_list.end())
			throw runtime_error("edit failed, song does not exist.");
		else
			song_list[song] = url;
	}

	//network related functions
	bool connect() {
		return true;
	}

	bool disconnect() {
		return true;
	}

	bool retire() {
		return true;
	}

};
} // end namespace dist

#endif // NODE_H