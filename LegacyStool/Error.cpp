#include "Error.h"
#include <iostream>

using namespace std;

void Error::print(Status status) {
	cerr << "Error: ";
	switch (status) {

	// no error
	case OK:	
		cerr << "no error"; break;
	case MATSTACK_INIT_ERR:
		cerr << "Bad initialization of matrix stack"; break;
	case MATSTACK_ERR:
		cerr << "Problem with the matrix stack"; break;
	default:	
		cerr << "undefined error code: " << status;
	}
	cerr << endl;
}