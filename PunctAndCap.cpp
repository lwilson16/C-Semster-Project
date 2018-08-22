#include <Reader.h>
#include <PunctAndCap.h>
#include <WordStem.h>
#include <ReadingLevel.h>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <utility>  
#include <cstddef>
using namespace std;

vector<string> PunctAndCap::exceptions;
bool PunctAndCap::ReadExceptions(char * argv){
	ifstream myFile1(argv);
	string exception;
	string replacement;
	string line;

	while(getline(myFile1, line))
	{
		istringstream words(line);
		if(words >> exception >> replacement)
		{
			if((words >> exception))
			{
				cerr << "Too many words on one line" << endl;
				return false;

			}
			else
			{
				//cout << "EXCEPTION: " << exception << endl;
				//cout << "REPLACEMENT: " << replacement << endl;
				exceptions.push_back(exception);
				exceptions.push_back(replacement);
				//cout << "HERE: " << exceptions.at(exceptions.size()-1) << endl;
				continue;
			}
		}
		
	 	else if((!(words >> exception >> replacement) == true) && (!myFile1.eof()))
		{
			cerr << "Too few words on one line" << endl;
			return false;
		}
		
		
	}
	myFile1.close();
	
	if (exceptions.size() == 0 || (!myFile1.eof() && myFile1.fail())){ 
		cout << "Exceptions file size: " << exceptions.size() << endl;
		cerr << "Invalid exceptions file" << endl;
		return false;
	}
	else 
		return true;
}
bool PunctAndCap::containsDigit(string& word){
	for(unsigned int i=0; i < word.length(); i++){
		if(isdigit(word.at(i)))
		{
			return true;
		}
	}
	return false;
}
bool PunctAndCap::contains(string word, char myChar){
	bool answer = false;
	size_t found;
	found = word.find_first_of(myChar);
	//cout << "contains word: " << word << endl;
	//cout << "char: " << myChar << endl;
	//cout << "Found: " << found << endl;
	if(found != string::npos)
	{
		answer = true;
	}
	return answer;
}

bool PunctAndCap::isAcronym(string word){
	bool answer = false;
	for(unsigned int i = 0; i < word.length(); i++)
	{
		char myChar = word.at(i);
		if((isupper(myChar)))
		{
			if(word.length() == 1)
			{
				answer = false;
			}
			else if(i > 0)
			{
				answer = true;
				break;
			}
		}
	}
	return answer;
}
bool PunctAndCap::isPunct(string word, unsigned int index){
	if(word.at(index) == '\'')
	{
		return false;
	}
	if(word.at(index) == ',')
	{
		if (validComma(word, index)  == false)
		{
			return true;
		}
		if (validComma(word, index)  == true)
		{
			return false;
		}
	}
	if(word.at(index) == '.')
	{
		if(validPeriod(word, index) == false)
		{
			return true;
		}
		if(validPeriod(word, index) == true)
		{
			return false;
		}
	}
	return ispunct(word.at(index));
}
bool PunctAndCap::needsSplit(string word, unsigned int index){
	bool answer;
	if((isPunct(word, index)))
	{
		if (index == 0)
		{
			answer = false;
		}
		
		else if(isPunct(word, index) 
			&& !isPunct(word, index-1))
		{
			answer = true;
		} 
		
		else if(!isPunct(word, index)
			&& isPunct(word, index-1))
		{
			answer = true;
		}
		else 
		{
			answer = false;
		}
		
	}
	if((index > 0) && !isPunct(word, index) && isPunct(word, index-1))
	{
		answer = true;
	}
	return answer;
}

bool PunctAndCap::validPeriod(string word, unsigned int index){
	bool answer;
	if(word.at(index) == '.')
	{
		/*checks if it is .01 format*/
		if((index == 0) && !(index == word.length()-1) &&  isdigit(word.at(index + 1)))
		{ 
			answer = true;
		}

		/*checks if it is 2.0 format*/
		else if(!(index == 0) && !(index == word.length()-1) &&  isdigit(word.at(index +1)) && isdigit(word.at(index - 1)))
		{
			answer = true;
		}

		else{ 
			//cout << "valid period is false"  << endl;
			answer = false;
			}	 
	}			
	return answer;
}

bool PunctAndCap::validComma(string word, unsigned int index){
	bool answer;
	if(word.at(index) == ',')
	{
		/*checks if it is 2,0 format*/
		if(!(index == 0) && !(index == word.length()-1) &&  isdigit(word.at(index +1)) && isdigit(word.at(index - 1)))
		{
			answer = true;
		}
		else 
			answer = false; 
	}
	return answer;
}
void PunctAndCap::split(string word){
	for(unsigned int i = 0; i < word.length(); i++)
	{
		if(needsSplit(word, i))
		{
			rawsplit.push_back(word.substr(0, i));
			
			if((i < word.length()))
			{
				split(word.substr(i));
			}
			return;
		}
	}
	rawsplit.push_back(word);
}
void PunctAndCap::separate2(vector<string>& myVector){
	//cout << "SIZE OF RAW VECTOR: " << myVector.size() << endl;
	for(unsigned int i = 0; i < myVector.size(); i++)
	{
		split(myVector.at(i));
	}
	//cout << "SIZE OF COPY: " << rawsplit.size() << endl;
}

bool PunctAndCap::EndOfSentence(string &word)
{
	for(unsigned int i = 0; i < word.length(); i++)
	{
		if(word.at(i) == '.' && !validPeriod(word, i) && !isAcronym(word))
		{
			return true;
		}
		else if(word.at(i) == '!' && !isAcronym(word))
		{
			return true;
		}
		else if(word.at(i) == '?' && !isAcronym(word))
		{
			return true;
		}
	}
	return false;
}
void PunctAndCap::capitalization(){/*check for capitalization*/
	for(unsigned int i = 0; i < rawsplit.size(); i++) 
	 {	 
		if(i == 0)
		{
			if(isAcronym(rawsplit.at(0)))
			{
				//cout << "HERE: " << rawsplit.at(i) << endl;
				continue;
			}
			else
			{
				if(isupper(rawsplit.at(0).at(0)))
				{
					rawsplit.at(0).insert((rawsplit.at(0).begin()), '+');
					continue;
				}
			}
		}

		else if(isupper(rawsplit.at(i).at(0)))
		{
			//cout << "COPY.AT(i): " << rawsplit.at(i) << endl;
			//cout << "PREVIOUS WORD: " << rawsplit.at(i-1) << endl;
			//cout << "END OF SENTENCE: " << EndOfSentence(rawsplit.at(i-1)) << endl; 
			if(EndOfSentence(rawsplit.at(i-1)) == true && !isAcronym(rawsplit.at(i)))
			{
				rawsplit.at(i).insert((rawsplit.at(i).begin()), '+');	
			}
		}

		else
		{
			continue;
		}
	 
	 }
	//cout << "SIZE OF EXCEPTIONS: " <<  exceptions.size() << endl;
	 
}
void PunctAndCap::readingLevel(){
	ReadingLevel document;
	//cout << "document: " << documentname << endl;
	document.sentences(rawsplit);
	document.letters(rawsplit);
	CL = document.compute();

}
string PunctAndCap::toLower(string &word)
{
	//cout << "toLower(word): " << word << endl;
	word.at(0) = tolower(word.at(0));
	return word;
}
bool PunctAndCap::exception(string &word){
	bool answer = false;
	for (unsigned int i = 0; i < exceptions.size(); i= i+2)
	{
		//cout << "Exceptions word: " << exceptions.at(i) << endl;
		if(exceptions.at(i) == word)
		{
			word = exceptions.at(i + 1);
			answer = true;	
		}
		
	}
	return answer;
}

void PunctAndCap::resolveCap(string &word, unsigned int index){
	//cout << "WORD: " << word << endl;
	/*if(word == "+A")
	{
		cout << "Is A " << word << endl;
	}*/
	
	word.erase(word.begin());
	for(unsigned int i = 0; i < rawsplit.size(); i++)
	{
		//cout << "WORD == Copy.at(i): " << (word == rawsplit.at(i)) << endl;
		if(word == rawsplit.at(i) && (i != index))
		{
			return;
		}
			
	}
	//cout << "WORD: " << word << endl;
		toLower(word);
		return;

}	

void PunctAndCap::stem(){
	WordStem vecWord;
	
	for(unsigned int i = 0; i < rawsplit.size(); i++)
	{
		//cout << "COPY.AT(i) " << rawsplit.at(i) << endl;
		if(rawsplit.at(i).at(0) == '+')
		{
			//cout << "COPY.AT(i): " << rawsplit.at(i) << endl;
			resolveCap(rawsplit.at(i), i);
		}
		if(rawsplit.at(i).size() <= 2)
		{
			continue;
		}
		if(containsDigit(rawsplit.at(i))){
			continue;
		}
		if(isupper(rawsplit.at(i).at(0)))
		{
			continue;
		}
		if(exception(rawsplit.at(i)) == true)
		{
			continue;
		}
		if(isAcronym(rawsplit.at(i)) == true)
		{
			continue;
		}
		else
		{
		vecWord.step1(rawsplit.at(i));
		vecWord.step2(rawsplit.at(i));
		vecWord.step3(rawsplit.at(i));
		vecWord.step4(rawsplit.at(i));
		vecWord.step5(rawsplit.at(i));
		vecWord.step6(rawsplit.at(i));
		vecWord.step7(rawsplit.at(i));
		vecWord.step8(rawsplit.at(i));
		}
		
	}
	sort(rawsplit.begin(), rawsplit.end());
}

void PunctAndCap::count(){
	/*comparing to the next element and counting occurrences */
	unique.push_back(make_pair(rawsplit.at(0), 1));
	for(unsigned int i = 0; i < rawsplit.size() -1 ; i++){
		if(rawsplit.at(i) != rawsplit.at(i+1)){
			unique.push_back(make_pair(rawsplit.at(i+1), 1));
		}
		else{
			unique.at(unique.size()-1).second++;
		}
	}
	
}


void PunctAndCap::print(){
	ofstream myFile;
	string temp;
	myFile.open(documentname+"_counts");
	for(unsigned int i = 0; i < unique.size(); i++){
			//cout << unique.at(i).first << " " << unique.at(i).second << endl;

		myFile << unique.at(i).first << " " << unique.at(i).second << endl;
	}
	myFile.close();
			
}
