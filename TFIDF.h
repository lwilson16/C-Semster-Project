#ifndef TFIDF_H
#define TFIDF_H

#include <iostream>
#include <fstream> //will be using to read from a file
#include <vector>
#include <string>
#include <Reader.h>
#include <PunctAndCap.h>

class TFIDF{
public:
	bool readExceptions(char * argv);
	bool readDocuments(char * argv);
	bool isPunctString(string word);
	double idf(string word);
	double tfidf(const PunctAndCap& Doc, string word, unsigned int index);
	double similarities(const PunctAndCap&  Doc1, const PunctAndCap& Doc2);
	void similarityScore();
	bool DocumentCL(const PunctAndCap & Doc, double range1, double range2);
	string compareDocuments(char * argv1, char * argv2);
	vector<PunctAndCap> myVector;
};
#endif
