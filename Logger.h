#ifndef LOGGER_H
#define LOGGER_H

#include <iomanip>		//setw
#include <iostream>		//cout, endl
#include <fstream>		//istream, ostream
#include <stdexcept>
#include <string>
#include <boost/lexical_cast.hpp>

using namespace std;

class Logger {
	bool display;
	int threshold;
	int num_lines;
	//ostringstream stream;
	string file;
	ofstream file_w;
	ifstream file_r;

	int process_id;

public:
	///\TODO: add custom string
	//Logger(bool disp, int thresh, ostringstream &out, string file = "") { }
	Logger() {
		display = true;
		threshold = 0;
		num_lines = 0;
		file = "";
		process_id = 0;
	}

	Logger(bool disp, int pid = 0, int thresh = 0) {
		display = disp;
		process_id = pid;
		threshold = thresh;
		num_lines = 0;

		file = boost::lexical_cast<string>("pid_") + boost::lexical_cast<string>(pid) + boost::lexical_cast<string>(".log");
		file_w.open(file.c_str());
		if (file_w.fail()) {
			file_w.close();
			throw runtime_error("Cannot create write log file.");
		}
	}

	///\TODO: delete write log?
	~Logger() {
		cout << "\n~Logger()" << endl;
		this->read();
		file_w.close();
		file_r.close();
	}

	///display entire stable storage
	void read() {
		file_r.open(file.c_str());
		if (file_r.fail()) {
			file_r.close();
			throw runtime_error("Cannot open write log file.");
		}

		int n=0;
		string line;
		while (!file_r.eof()) {
			getline(file_r,line);
			if (file_r.good())
				cout << file << "[" << setw(4) << ++n << "]: " << line << endl;
		}

		file_r.close();
	}

	///display first n lines of stable storage
	///\TODO: modify output to match read()
	void read_head(int num) {
		cout << ">>>displaying first " << num << " lines of write log [" << file << "]" << endl;
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
	///\TODO: modify output to match read()
	void read_tail(int num) {
		cout << ">>>displaying last " << num << " lines of write log [" << file << "]" << endl;
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

	template <typename T>
	void set_file(const T &input) {
		file_w.close();
		file_r.close();
		file = boost::lexical_cast<string>(input);
		file_w.open(file.c_str());
		if (file_w.fail()) {
			file_w.close();
			throw runtime_error("Cannot create write log file.");
		}
	}

	template <typename T>
	void write(int thresh, T input) {
		if (thresh >= threshold)
			cout << file << "[" << setw(4) << num_lines+1 << "]:\t" << input << endl;
		write(input);
	}

	template <typename T>
	void write(const T &input) {
		file_w.clear();
		file_w << input << endl;
		++num_lines;
		if (file_w.fail()) {
			file_w.close();
			throw runtime_error("Cannot write to log file.");
		}
	}

private:
	template <typename T>
	void print(const int &n, const T &input) const {
		cout << file << "[" << setw(4) << n << "]: " << input << endl;
	}
};

#endif // LOGGER_H
