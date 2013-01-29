#ifndef ERROR_H
#define ERROR_H

enum Status {
// no error
	OK = 0, NOTUSED = -999,

// matrix stack errors
	MATSTACK_INIT_ERR, MATSTACK_ERR,

};

class Error {
public:
	static void print(Status status);
};

#endif