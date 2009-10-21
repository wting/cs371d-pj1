#ifndef LOGGER_H
#define LOGGER_H

#include <cassert>
#include <iostream>
#include <new>
#include <sstream>
#include <stdexcept>
#include <string>

#ifdef DEBUG_OUTPUT
	#define debug(arg) cout << (arg) << endl;
#else
	#define debug(arg) /* arg */
#endif

using namespace std;

class Logger {
	bool display;
	int threshold;
	ostringstream stream;
	string log;

	public:
	///\TODO: add custom string
	//Logger(bool disp, int thresh, ostringstream &out, string file = "") { }
	Logger(bool disp, int thresh, string file = "") {
		display = disp;
		threshold = thresh;
		log = file;
	}

	Logger(bool disp) {
		display = disp;
		if (disp)
			threshold = 1000;
		else
			threshold = 0;
	}

	///display entire stable storage
	void read() {

	}

	///display past n lines of stable storage
	void read(int n) {

	}

	///display past n lines of stable storage above threshold
	void read(int thres, int n) {

	}

	void write(int thresh, string line) {
		///\TODO: write line to stable storage
		if (thresh >= threshold)
			cout << "line" << endl;
	}

	void write(string line) {
		///\TODO: write line to stable storage
	}
};

#endif // LOGGER_H
