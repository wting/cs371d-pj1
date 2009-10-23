#ifndef NODE_H
#define NODE_H

#include <stdexcept>
#include <string>
#include <boost/unordered_map.hpp>
#include <boost/asio.hpp>
#include "logger.h"

using namespace std;
namespace dist {

class node {
	boost::unordered_map<string, string> song_list;
	boost::unordered_map<string, string> node_list;

	//socket related stuff
	boost::asio::io_service io;
	string socket;
	string status;
	int socket_num;

	logger* log;

public:
	node(logger* l) {
		socket_num = 10000;
		log = l;
		log->write(0,"node constructor");
	}

	~node() {
		log->write(0,"node destructor");
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
