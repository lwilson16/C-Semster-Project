#include <iostream>
#include <fstream>
#include <Reader.h>
#include <PunctAndCap.h>
#include <ReadingLevel.h>
#include <TFIDF.h>

using namespace std;
int main(int argc, char* argv[]){
	Reader myFile; 
	PunctAndCap words;
	TFIDF documents;

	if (argc != 5){
		cerr << "Incorrect number of arguments" << endl;
		return -1;
	}

	if(documents.readDocuments(argv[2]) != true){
				return -1;
	}

	if (myFile.Read(argv[1]) != true){
			return -1;
	}
	
	else{
		words.documentname = argv[1];
		words.separate2(myFile.myVector);
		//cout << "SIZE OF COPY: " << words.copy.size() << endl;
		words.capitalization();
		words.stem();
		words.count();
		//words.print();
		documents.myVector.insert(documents.myVector.begin(), words);


		if(documents.compareDocuments(argv[3], argv[4]) == "")
		{
			cerr << "No documents are within range " << endl;
			return -1;
		}
				
		
	}

}
