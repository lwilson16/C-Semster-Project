#ifndef READING_LEVEL_H
#define READING_LEVEL_H

#include <fstream> 
#include <vector>
#include <string>
#include <PunctAndCap.h>

using namespace std;

class ReadingLevel: public PunctAndCap{
public:
	bool validPeriod(string word, unsigned int index);
	bool validComma(string word, unsigned int index);
	bool isEndOfSentencePunct(string word, unsigned int index);
	bool isEndOfSentence(string word);
	bool isPunctString(string word);
	bool isLetter(string word, unsigned int index);

	void sentences(vector<string>& unique);
	void letters(vector<string>& unique);
	double compute();
	
	int wordcounter;  
	int scounter = 0;
	int lcounter = 0;
	double numSentences=0;
	double numLetters=0;
	
};
#endif
