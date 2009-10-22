#ifndef LOGGER_H
#define LOGGER_H

#include <iomanip>		//setw
#include <iostream>		//cout, endl
#include <fstream>		//istream, ostream
#include <stdexcept>
#include <string>

using namespace std;

class Logger {
	bool display;
	int threshold;
	//ostringstream stream;
	string file;
	ofstream file_w;
	ifstream file_r;

	public:
	///\TODO: add custom string
	//Logger(bool disp, int thresh, ostringstream &out, string file = "") { }
	Logger() {
		display = true;
		threshold = 0;
		file = "";
	}

	Logger(bool disp, int thresh=0, string name = "") {
		display = disp;
		threshold = thresh;
		file = name;
		file_w.open(name.c_str());
		if (file_w.fail()) {
			file_w.close();
			throw runtime_error("Cannot create write log file.");
		}
	}

	///\TODO: delete write log?
	~Logger() {
		file_w.close();
		file_r.close();
	}

	///display entire stable storage
	void read() {
		cout << ">>>displaying write log" << endl;
		file_r.open(file.c_str());
		if (file_r.fail()) {
			file_r.close();
			throw runtime_error("Cannot open write log file.");
		}

		int n=1;
		string line;
		while (!file_r.eof()) {
			getline(file_r,line);
			if (file_r.good())
				cout << setw(8) << n++ << ": " << line << endl;
		}

		file_r.close();
	}

	///display first n lines of stable storage
	void read_head(int num) {
		cout << ">>>displaying first " << num << " lines of write log" << endl;
		file_r.open(file.c_str());
		if (file_r.fail()) {
			file_r.close();
			throw runtime_error("Cannot open write log file.");
		}

		int n=1;
		string line;
		while (n <= num && !file_r.eof()) {
			getline(file_r,line);
			cout << setw(8) << n++ << ": " << line << endl;
		}

		file_r.close();
	}

	///display last n lines of stable storage
	void read_tail(int num) {
		cout << ">>>displaying last " << num << " lines of write log" << endl;
		file_r.open(file.c_str());
		if (file_r.fail()) {
			file_r.close();
			throw runtime_error("Cannot open write log file.");
		}

		//count number of lines
		int size = -1;
		string line;
		while (!file_r.eof()) {
			getline(file_r,line);
			++size;
		}

		//display last num lines
		file_r.close();
		file_r.open(file.c_str());
		int n = 1;
		//file_r.seekg(0);
		//file_r.clear();
		while (!file_r.eof()) {
			getline(file_r,line);
			if (n > (size - num) && file_r.good())
				cout << setw(8) << n << ": " << line << endl;
			++n;
		}

		file_r.close();
	}

	///display past n lines of stable storage above threshold
	void read(int thres, int n) {

	}

	void set_file(string name) {
		file_w.close();
		file_r.close();
		file = name;
		file_w.open(name.c_str());
		if (file_w.fail()) {
			file_w.close();
			throw runtime_error("Cannot create write log file.");
		}
	}

	void write(int thresh, string line) {
		if (thresh >= threshold)
			cout << line << endl;
		write(line);
	}

	void write(string line) {
		file_w.clear();
		file_w << line << endl;
		if (file_w.fail()) {
			file_w.close();
			throw runtime_error("Cannot write to log file.");
		}
	}
};

#endif // LOGGER_H
