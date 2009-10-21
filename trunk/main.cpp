/**
	\file main.cpp
	\brief CS 371D Project - Playlist Editing

	\author HanPing Ting
	\author Will Warner
*/

#include "Logger.h"
#include "Node.h"

#ifdef DEBUG_OUTPUT
	#define debug(arg) cout << (arg) << endl;
#else
	#define debug(arg) /* arg */
#endif

int main(int argc, char* argv[]) {
    using namespace std;
    using namespace dist;

	/*Node* A = new Node();
	delete A;
	*/

	Logger log(true,0,"socket_fake.log");

	string input;
	while (true) {
		cin >> input;
		if (cin.eof())
			break;
		log.write(0,"input line: " + input);
	}

	log.read();
	//log.read_head(1);
	//log.read_tail(2);
    return 0;
}
