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

	Node* A = new Node();

	delete A;

    return 0;
}
