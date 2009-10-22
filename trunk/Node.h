#ifndef NODE_H
#define NODE_H

#include <stdexcept>
#include <string>
#include <boost/unordered_map.hpp>
#include <boost/lexical_cast.hpp>
//#include <boost/asio.hpp>
#include "Logger.h"

using namespace std;
using namespace boost;
namespace dist {

class Node {
	unordered_map<string, string> song_list;
	unordered_map<string, string> node_list;
	Logger log;

	string socket;
	string status;
	int socket_num;

    public:
	Node() {
		socket_num = 10000;
		log.set_file(lexical_cast<string>("socket_") + lexical_cast<string>(socket_num) + lexical_cast<string>(".log"));
		log.write(0,"socket_num: " + lexical_cast<string>(socket_num));
	}

	~Node() {
		log.read();
	}

	void parse(string in) {
		log.write(5,"input: " + in);
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
