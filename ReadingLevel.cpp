#include <ReadingLevel.h>
#include <PunctAndCap.h>
#include <algorithm>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>


using namespace std;
bool ReadingLevel::validPeriod(string word, unsigned int index){
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
bool ReadingLevel::validComma(string word, unsigned int index){
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
bool ReadingLevel::isEndOfSentencePunct(string word, unsigned int index){
/**checks if a string contains an end of line character
 * need to make sure that I am not testing for valid periods
 * can be a . ? ! point in the middle of a punctuation string as well
 */
	bool answer = false;
	
		/*if(word.at(index) == '\'')
		{
			answer = false;
		}*/
	
		if(word.at(index) == '.')
		{
			answer = true;
		}
		else if(word.at(index) == '!')
		{
			answer = true;	
		}
		else if(word.at(index) == '?')
		{
			answer =  true;
		}
		
	return answer;
}
bool ReadingLevel::isEndOfSentence(string word){
 	for(unsigned int i = 0; i < word.length() ; i++)
	{
		if(isEndOfSentencePunct(word, i) && !validPeriod(word, i))
		{
			return true;
		}
	}
	
	return false;
}
bool ReadingLevel::isPunctString(string word){
/**checks if I have a string of purely punctuation
 * param word does this by checking the first and second character
 * if there is a + at the beginning of a word it is NOT a punctuation strin
 */
	//cout << "WORD ending: " << word.length()-1 << endl;
	if(word.at(word.length()-1) == '\'')
	{
		return false;
	}
	else
	{
		return ispunct(word.at(word.length()-1));
	}
}

bool ReadingLevel::isLetter(string word, unsigned int index){
/**checks if it is a letter for the letter counter method
 * \ apostrophes are considered letters
 */
	bool answer = false;
	
	if((word.at(index) == '\'') 
		|| (isalpha(word.at(index)))
		|| (isdigit(word.at(index))))
	{
		answer = true;
	}
	return answer;
}

void ReadingLevel::sentences(vector<string>& unique){
/**Calcaulates the number of sentences
 * \a sentence can be calculated by the amount of end of line
 * \punctuation characters there are
 */
	wordcounter = unique.size();
	double sw;
	for(unsigned int i = 0; i < unique.size(); i++)
	{
		//cout << "WORD: " << unique.at(i) << endl;
		//cout << "scounter: " << scounter << endl;
		if(isEndOfSentence(unique.at(i)))
		{
			scounter++;
		}
		if(isPunctString(unique.at(i)))
		{
			wordcounter = wordcounter -1;
		}
	}
	sw = ((double)scounter / wordcounter);
	/*cout << "scounter: " << scounter << endl;
	cout << "wordcounter: " << wordcounter << endl;
	cout << "SW: " << sw << endl;*/
	numSentences = ( sw * 100);
	
}

void ReadingLevel::letters(vector<string>& unique){
/**This class calculates the number of letters per 100 words
 * \uses the unique vector which contains the split words
 * \calculates numLetters by dividing lcounter and wordcounter
 * \wordcounter is the size of the vector - number of punctuation strings
 */

	for(unsigned int i = 0; i < unique.size(); i++)
	{
		for(unsigned int j = 0; j < unique.at(i).size(); j++)
		{
			if(isLetter(unique.at(i), j) || validPeriod(unique.at(i), j))
			{
				lcounter++;
			}
		}
	}
	numLetters = (((double)lcounter/wordcounter) * 100);
	//cout << "numLetters: " << numLetters << endl;
}

double ReadingLevel::compute(){
	double CL = 0;
	//cout << "WORDCOUNT: " << wordcounter << endl;
	//cout << "NUMBER OF LETTERS: " << lcounter << endl;
	//cout << "NUMBER OF SENTENCES: " << scounter << endl;
	//cout << "S(doc): " << numSentences << endl;
	//cout << "L(doc) " << numLetters << endl;
	CL = ((0.0588 * numLetters) - (0.296 * numSentences) - 15.8);
	return CL;
}
