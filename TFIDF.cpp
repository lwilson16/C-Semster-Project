#include <iostream>
#include <fstream>
#include <PunctAndCap.h>
#include <TFIDF.h>
#include <algorithm>
#include <vector>
#include <string>
#include <math.h>
#include <iomanip>
#include <utility>  
#include <cstddef>

using namespace std;
bool TFIDF::readExceptions(char * argv){
	PunctAndCap exceptions;
	if(!exceptions.ReadExceptions(argv)){
		return false;
	}
	else
		return true;
}
bool TFIDF::readDocuments(char *argv){
	ifstream myFile(argv); //Begins reading from a file
	string temp;
	unsigned int i = 1;
	while(myFile >> temp){
		PunctAndCap document;
		Reader myReader;
		if(i == 1)
		{
			if(!readExceptions((char * )temp.c_str()))
			{
				return false;
			}
			i++;
		}
		else{
			document.documentname = temp;
			if(!myReader.Read((char *) temp.c_str())){
				cerr << "Invalid file " << endl;
				return false;
			}

			else{
			document.separate2(myReader.myVector);
			document.capitalization();
			document.readingLevel();
			document.stem();
			document.count();
			document.print();
			myVector.push_back(document);
			}
		}
	}
	return true;
}
bool TFIDF::isPunctString(string word){
	bool answer = false;
	
	//check for apostrophes
	if(ispunct(word.at(word.length()-1)) && word.at(word.length()-1) != '\'')
	{
		answer = true;
	}
	
	return answer;
}
double TFIDF::idf(string word){
int count = 0; //the number of documents containing at least one instance of the word
double idf = 0; //idf for each word in unique is reset to 0 

	for(unsigned int i = 0; i < myVector.size(); i++)
	{
		
		for(unsigned int j  = 0; j < myVector.at(i).unique.size(); j++)
		{			
			if(myVector.at(i).unique.at(j).first == word)
			{	
				//cout << "Result: " << myVector.at(i).unique.at(j) << endl;
				count++;
				break;
			}
		}
	}	
		idf = log10((double)myVector.size() / count);
		//cout << "Word: " << word << endl;
		//cout << "Occurences: " << count << endl;
		//cout << "IDF : " << idf << endl;
		return idf;

}
double TFIDF::tfidf(const PunctAndCap & Doc, string word, unsigned int index){

	double tfidf;
	tfidf = (double) Doc.unique.at(index).second * idf(word); 
	return tfidf;

}
double TFIDF::similarities(const PunctAndCap & Doc1, const PunctAndCap & Doc2){
/*calculate the similarity score
 * go through the unique element vector for each document
 * multiply the two tfidf scores together
 */
	double similarityscore = 0;
	for(unsigned int i = 0; i < Doc1.unique.size(); i++)
	{	
		for(unsigned int j = 0; j < Doc2.unique.size(); j++)
		{
			
			if((Doc1.unique.at(i).first == Doc2.unique.at(j).first) && (!isPunctString(Doc1.unique.at(i).first) && !isPunctString(Doc2.unique.at(j).first)))
			{
				similarityscore += tfidf(Doc1, Doc1.unique.at(i).first, i) * tfidf(Doc2, Doc2.unique.at(j).first,j);
			
			}
		}	
	}
	//cout << "Similarity score: " << similarityscore << endl;
	return similarityscore;	
}
void TFIDF::similarityScore(){
/*calculate the similarity score by calling the similarity function
 * only takes two documents at a time since you are comparing every two documents
 */	
	for(unsigned int i = 1; i < myVector.size(); i++)
	{
		//ASK ABOUT THIS IF THIS IS VALID
		myVector.at(i).similarityScore = similarities(myVector.at(0), myVector.at(i));
	}
}
bool TFIDF::DocumentCL(const PunctAndCap & Doc, double range1, double range2){
	//cout << "NAME: " << Doc.documentname << endl;
	//cout << "Range1: " << range1 << endl;
	//cout << "Range2: " << range2 << endl;
	//cout << "Document CL: " << Doc.CL << endl;
	if (Doc.CL >= range1 && Doc.CL <= range2){
		return true;
	}
	else 
	{
		return false;
	}
}
string TFIDF::compareDocuments(char* argv1, char* argv2){

	ifstream myint;
	double range1 = atof(argv1);
	double range2 = atof(argv2);
	double bestScore = 0;
	string myString = ""; //check if empty in main

	//cout << "Range 1: " << range1 << endl;
	//cout << "Range 2: " << range2 << endl;

	if(range2 < range1)
	{
		cerr << "Invalid range" << endl;
		return myString;
	}
	
	else
	{
		similarityScore();

		for(unsigned int i = 0; i < myVector.size(); i++)
		{
			//cout << "Checking document: " << myVector.at(i).documentname << endl;
			//cout << "DocumentCL valid: " << DocumentCL(myVector.at(i), range1, range2) << endl;
			//cout << "DocumentCL: " << myVector.at(i).CL << endl;
			
			if(DocumentCL(myVector.at(i), range1, range2))
			{
				//cout << "Document within range " << endl;
				//cout << "Similarity score: " << myVector.at(i).similarityScore << endl;
				if(myVector.at(i).similarityScore > bestScore)
				{

					bestScore = myVector.at(i).similarityScore;
					myString = myVector.at(i).documentname;

				}

			}
		}
	}
	
	cout << myString << endl;
	return myString;
}

