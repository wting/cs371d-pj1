#ifndef NODE_H
#define NODE_H

#include <cassert>
#include <iostream>
#include <new>
#include <stdexcept>
#include <string>
#include <unordered_map>

#ifdef DEBUG_OUTPUT
	#define debug(arg) cout << (arg) << endl;
#else
	#define debug(arg) /* arg */
#endif

using namespace std;
namespace dist {

class Node {
	string socket;
	string status;
	unordered_map<string, string> song_list;
	unordered_map<string, string> node_list;
    public:
	Node() {
	}

	//Song related functions
	void add(string song) {
	}

	void del(string song) {
	}

	void edit(string song, string url) {
	}

	//Node related functions
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
