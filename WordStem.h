#ifndef Word_Stem_H
#define Word_Stem_H

#include <iostream>
#include <fstream> //will be using to read from a file
#include <vector>
#include <string>
#include <Reader.h>
#include <PunctAndCap.h>

using namespace std;

class WordStem{
public: 
	int findfirstvowel(string& word);
	bool isVowel(string word, unsigned int index);
	bool isConsonant(string word, unsigned int index);
	bool containsVowel(string word);

	bool isDouble(string &word);
	bool isValidLiEnding(string word);
	string Region1(string word, bool beginswithy);
	string Region2(string word);
	bool isSuffix(string word, string suf); 

	string preceder(string &word, string suf);
	bool isShortSyl(string &word);
	bool isShort(string &word);
	bool contains(string word, string suf);
	
	string step1(string &word, string suf);
	string step1(string &word);
	string step2(string &word, string suf);
	string step2(string &word);
	string step3(string &word, string suf);
	string step3(string &word);
	string step4(string &word);
	string step5(string &word, string suf);
	string step5(string &word);
	string step6(string &word, string suf);
	string step6(string &word);
	string step7(string &word, string suf);
	string step7(string &word);
	string step8(string &word, string suf);
	string step8(string &word);
private:
	string suffix;
	string precede; 	
};
#endif
