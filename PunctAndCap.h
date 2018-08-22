#ifndef Punct_And_Cap_H
#define Punct_And_Cap_H


#include <iostream>
#include <fstream> //will be using to read from a file
#include <vector>
#include <string>
#include <vector>
#include <string>
#include <Reader.h>
#include <WordStem.h>

using namespace std;

class PunctAndCap: public Reader{
public:
	bool ReadExceptions(char * argv);
	bool containsDigit(string& word);
	bool contains(string word, char myChar);
	bool isAcronym(string word);
	bool isPunct(string word, unsigned int index);
	bool needsSplit(string word, unsigned int index);
	bool validPeriod(string word, unsigned int index);
	bool validComma(string word, unsigned int index);
	void split(string word); //pushes strings from word onto vec2
	void separate2(vector<string>& myVector);
	bool EndOfSentence(string &word);
	void capitalization();
	void readingLevel();
	string toLower(string &word);
	bool isException(vector<string>& exceptions);
	bool exception(string &word);
	void resolveCap(string &word, unsigned int index);
	void stem();
	void count();
	void print();

	string documentname;
	static vector<string> exceptions;
	vector<pair<string, int> > unique;
	vector<string> rawsplit;
	double CL;
	double similarityScore;
};
#endif

