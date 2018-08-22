#include <Reader.h>
#include <iostream>
#include <fstream> //will be using to read from a file
#include <sstream>
#include <vector>
#include <string>

using namespace std;
bool Reader::Read(char * argv){
	ifstream myFile(argv); //Begins reading from a file
	
	//ASK: if i can check if my file is open in here !! 
	string temp;
	while (myFile >> temp){
		myVector.push_back(temp);
	}
	
	//myFile.close();

	if (myVector.size() == 0 || (!myFile.eof() && myFile.fail())){
		cout << "EOF: " << myFile.eof() << endl;
		cout << "Fail(): " << myFile.fail() << endl; 
		cerr << "Invalid file" << endl;
		return false;
	}
	
	else
		return true;
	
	
}
