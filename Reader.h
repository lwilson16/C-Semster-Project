#ifndef READER_H
#define READER_H

#include <iostream>
#include <fstream> //will be using to read from a file
#include <vector>
#include <string>

using namespace std;

class Reader{
public:
	bool Read(char* argv);
	vector <string> myVector;
};
#endif
