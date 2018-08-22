#include <WordStem.h>
#include <vector>
#include <string>
#include <cstddef>

using namespace std;
int WordStem::findfirstvowel(string& word){
	for(unsigned int i = 0; i < word.length(); i++){
		if(isVowel(word,i)){
			return i;
		}
	}
	return word.length();
}
bool WordStem::isVowel(string word, unsigned int index){
	char myChar;
	bool answer = false;
	myChar = word.at(index);
	if((myChar == 'a') 
		|| (myChar == 'e') 
		|| (myChar == 'i') 
		|| (myChar == 'o')
		|| (myChar == 'u'))
	{
		answer = true;
	}
	else if(myChar == 'y')
	{
		if(index == 0)
		{
			answer = false;
		}
		else if((index > 0) && isVowel(word, index-1))
		{
			answer = false;
		}
		else
		{
			//cout << "HERE" << endl;
			answer = true;
		}
	}
		          
      return answer;               
}
bool WordStem::isConsonant(string word, unsigned int index){
	bool answer = false;
	if(isVowel(word, index) == false && word.at(index) != '\''){
		answer = true;
	}
	return answer;
}

bool WordStem::containsVowel(string word){
	bool found = false;
	for(unsigned int i = 0; i < word.length(); i++)
	{
		//cout << "WORD AT I: " << word.at(i) << endl;
		if(isVowel(word, i))
		{
			found = true;
			return found;
		}

	}
	return found;
}

bool WordStem::isDouble(string &word){
	string Double = word.substr(word.length()-2, 2); 
	if(Double == "bb" 
		|| Double == "dd" 
		|| Double == "ff" 
		|| Double == "gg" 
		|| Double == "mm" 
		|| Double == "nn" 
		|| Double == "pp" 
		|| Double == "rr" 
		|| Double == "tt"){
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

bool WordStem::isValidLiEnding(string word){
	if(word.at(word.length()-1) == 'c' 
		||word.at(word.length()-1)== 'd' 
		||word.at(word.length()-1)== 'e' 
		||word.at(word.length()-1)== 'g' 
		||word.at(word.length()-1)== 'h' 
		||word.at(word.length()-1)== 'k' 
		||word.at(word.length()-1)== 'm' 
		||word.at(word.length()-1)== 'n' 
		||word.at(word.length()-1)== 'r' 
		||word.at(word.length()-1)== 't')
	{
		return true;
	}
	else
	{ 
		return false;
	}
	return false;
}

string WordStem::Region1(string word, bool beginswithy = false){
	string R1 = "";
	for(unsigned int i = 0; i < word.length()-1; i++)
	{
		if((isVowel(word, i) || beginswithy) 
			&& isConsonant(word, i+1))
		{
			R1 = word.substr(i+2 , word.length()-1);
			break;
		}	
	}
	//cout << "R1: " << R1 << endl;
	return R1;
}

string WordStem::Region2(string word){
	//cout << "WORD: " << word << endl;
	string R2 = "";
	string newR2 = "";
	R2 = Region1(word);
	
	if (R2.length() > 2)
	{
		bool isY = R2.at(0) == 'y' && isVowel(word, word.length() - R2.length());
		newR2 = Region1(R2, isY);
			return newR2;
	}
	else 
		return newR2;
}

bool WordStem::isSuffix(string word, string suf){
bool answer = false;	
string suffix;
	if(word.length() >= suf.length())
	{
		suffix = word.substr(word.length()-suf.length());
		answer  = (suf.compare(suffix) == 0);
		
	}	
	return answer;
		
}

string WordStem::preceder(string &word, string suf){
	if(isSuffix(word, suf))
	{
		return word.substr(0, word.length()-suf.length());
	}
	
	return word;
}

bool WordStem::isShortSyl(string &word){
bool answer = false;
	//cout << "isShortSyl: " << word << endl;
	if((word.length() >= 3) 
		&& isConsonant(word, word.length()-3) 
		&& isVowel(word, word.length()-2) 
		&& isConsonant(word, word.length()-1)
		&& word.at(word.length()-1) != 'w'
		&& word.at(word.length()-1) != 'x'
		&& word.at(word.length()-1) != 'y')
	{
		answer = true;
	}

	else if(word.length() == 2 
		&& isVowel(word, 0) 
		&& (isConsonant(word, word.length()-1)))
	{
		 answer = true;
	}	
	return answer;
}

bool WordStem::isShort(string &word){
	bool answer = false;
	//cout << "isShort: " << word << endl;
	if ((isShortSyl(word) == true) 
		&& Region1(word).empty())
	{
		answer = true;
	}
	return answer;
}

bool WordStem::contains(string word, string suf){
	//cout << "Contains: " << word << endl;
	bool answer = false;
	if((word.length() > suf.length())
		|| (word.length() == suf.length()))
		
	{
		word = word.substr(word.length()-suf.length());
		if(suf.compare(word) == 0)
		{
			answer = true;
		}
	}
	return answer;
}

string WordStem::step1(string &word, string suf){
	if(isSuffix(word, suf))
	{
		word = word.substr(0, word.length()-suf.length());
	}
	return word;
}
string WordStem::step1(string &word){

	if(word.at(0) == '\'')
	{
		word.erase(word.begin());
	}
	
	if(isSuffix(word , "'s'"))
	{
		word = step1(word, "'s'");
	}

	if(isSuffix(word , "'s"))
	{
		word = step1(word, "'s");
	}

	if(isSuffix(word , "\'"))
	{
		//cout << "Word: " << word << endl;
		word = step1(word, "\'");
		//cout << "Word after: " << word << endl;
	}

	return word;
}

string WordStem::step2(string &word, string suf)
{
	if(isSuffix(word, suf))
	{
		word = word.substr(0, word.length()-suf.length());
	}
	return word;

}
string WordStem::step2(string &word){
	if(isSuffix(word, "sses"))
	{
		step2(word, "sses");
		word += "ss";
	}
	else if(isSuffix(word, "ied"))
	{
		precede = preceder(word, "ied");
		if (precede.length() > 1)
		{
			word = precede;
			word += "i";			
		}
	
		else
		{	
			word = precede;
			word += "ie";
		}
				
	}
	else if(isSuffix(word, "ies"))
	{
		precede = preceder(word, "ies");
		if (precede.length() > 1)
		{
			word = precede;
			word += "i";			
		}
		else{
			word = precede;
			word += "ie";
		}
				
	}

	else if (isSuffix(word, "us"))
	{
		word = step2(word, "us");
		word += "us";
	}
	else if (isSuffix(word, "us"))
	{
		word = step2(word, "us");
		word += "us";
	}
	else if (isSuffix(word, "ss"))
	{
		word = step2(word, "ss");
		word += "ss";
	}
	else if (isSuffix(word, "s"))
	{
		//ASK!!!!!!
		precede = preceder(word, "s");
		
		if (containsVowel(precede))
		{
			if(findfirstvowel(precede) != precede.length()-1)
			{
				word = precede;
			}
		}
	}
		return word;
}

string WordStem::step3(string &word, string suf)
{
	if(isSuffix(word, suf))
	{
		word = word.substr(0, word.length()-suf.length());
	}
	return word;

}

string WordStem::step3(string &word){
	 if(isSuffix(word, "eedly"))
	{
		if(contains(Region1(word), "eedly") == true)
		{
			word = step3(word, "eedly");
			word += "ee";
		}
	}
	
	else if(isSuffix(word, "eed"))
	{
		if(contains(Region1(word), "eed") == true)
		{
			word = step3(word, "eed");
			word += "ee";
		}
	}		
		
	else if (isSuffix(word, "ed"))
	{
		precede = preceder(word, "ed");
		if(precede.length() < 2)
		{
			return word;
		}
		
		else
		{
			string ending = precede.substr(precede.length()-2);
			//cout << "PRECEDER: " << precede << endl;
			//cout << "ENDING: " << ending << endl;
			if(containsVowel(precede))
			{
				if((ending == "at") 
					|| (ending == "bl") 
					|| (ending == "iz"))
				{
					word = precede; 
					word += "e";
				}
				else if(isDouble(ending))
				{
					word = precede;
					word.erase(word.length()-1, word.length());
				}
				else if(isShort(precede))
				{
					word = precede;
					word += "e";
				}
				else
				{
					word = precede;
				}
			}
		}
	}

	else if (isSuffix(word, "edly"))
	{
		precede = preceder(word, "edly");\
		if(precede.length() < 2)
		{
			word += "edly";
		}
		else
		{
			string ending = precede.substr(precede.length()-2);
			if(containsVowel(precede))
			{
				if(contains(ending, "at") 
					|| contains(ending, "bl") 
					|| contains(ending, "iz"))
				{
					word = precede; 
					word += "e";
				}
				else if(isDouble(ending))
				{
					word = precede;
					word.erase(word.length()-1, word.length());
				}
				else if(isShort(precede))
				{
					word = precede;
					word += "e";
				}
				else 
				{
					word = precede;
				}
			}
		}
	}

	else if (isSuffix(word, "ing"))
	{
		//cout << "WORD: " << word << endl;
		precede = preceder(word, "ing");

		if(precede.length() < 2)
		{
			return word;
		}
		else
		{		
			string ending = precede.substr(precede.length()-2);
			if(containsVowel(precede))
			{
				if(contains(ending, "at") 
					|| contains(ending, "bl") 
					|| contains(ending, "iz"))
				{
					word = precede; 
					word += "e";
				}
				else if(isDouble(ending))
				{
					word = precede;
					word.erase(word.length()-1, word.length());
				}
				else if(isShort(precede))
				{
					word = precede;
					word += "e";
				}
				else
				{
					word = precede;
				}
			}
		}
	}

	else if (isSuffix(word, "ingly"))
	{
		precede = preceder(word, "ingly");
		if(precede.length() < 2)
		{
			word += "ingly";
		}
		else{
			string ending = precede.substr(precede.length()-2);
			if(containsVowel(precede))
			{
				if(ending == "at" 
					|| ending == "bl" 
					|| ending == "iz")
				{
					word = precede; 
					word += "e";
				}
				else if(isDouble(ending))
				{
					word = precede;
					word.erase(word.length()-1, word.length());
				}
				else if(isShort(precede))
				{
					word = precede;
					word += "e";
				}
				else 
				{
					word = precede;
				}
			}
		}
	}

	return word;
}

string WordStem::step4(string &word){
	if(isSuffix(word, "y"))
	{
		precede = preceder(word, "y");
		if((precede.length() >= 2)
			&& (isConsonant(precede, precede.length()-1) == true))
		{
			word = precede;
			word += "i";
		}
		
	}
	return word;	
}

string WordStem::step5(string &word, string suf)
{
	if(isSuffix(word, suf))
	{
		word = word.substr(0, word.length()-suf.length());
	}
	return word;

}

string WordStem::step5(string &word){
	if(isSuffix(word, "ational"))
	{
		word = step5(word, "ational");
		word+="ate";
	}
	else if(isSuffix(word, "ization"))
	{
		word = step5(word, "ization");
		word+="ize";
	}
	else if(isSuffix(word, "tional"))
	{
		word = step5(word, "tional");
		word+="tion";
	}
	else if(isSuffix(word, "enci"))
	{
		word = step5(word, "enci");
		word+= "ence";
	}
	else if(isSuffix(word, "anci"))
	{
		word = step5(word, "anci");
		word+="ance";
	}
	else if(isSuffix(word, "abli"))
	{
		word = step5(word, "abli");
		word+="able";
	}
	else if(isSuffix(word, "entli"))
	{
		word = step5(word, "entli");
		word+="ent";
	}
	else if(isSuffix(word, "izer"))
	{
		word = step5(word, "izer");
		word+="ize";
	}
	else if(isSuffix(word, "ation"))
	{
		word = step5(word, "ation");
		word+="ate";
	}
	else if(isSuffix(word, "ator"))
	{
		word = step5(word, "ator");
		word+="ate";
	}
	else if(isSuffix(word, "alism"))
	{
		word = step5(word, "alism");
		word+="al";
	}
	else if(isSuffix(word, "aliti"))
	{
		word = step5(word, "aliti");
		word+="al";
	}
	else if(isSuffix(word, "alli"))
	{
		word = step5(word, "alli");
		word+="al";
	}
	else if(isSuffix(word, "fulness"))
	{
		word = step5(word, "fulness");
		word+="ful";
	}
	else if(isSuffix(word, "ousli"))
	{
		word = step5(word, "ousli");
		word+="ous";
	}
	else if(isSuffix(word, "ousness"))
	{
		word = step5(word, "ousness");
		word+="ous";
	}
	else if(isSuffix(word, "iveness"))
	{
		word = step5(word, "iveness");
		word+="ive";
	}
	else if(isSuffix(word, "iviti"))
	{
		word = step5(word, "iviti");
		word+="ive";
	}
	else if(isSuffix(word, "biliti"))
	{
		word = step5(word, "biliti");
		word+="ble";
	}
	else if(isSuffix(word, "bli"))
	{
		word = step5(word, "bli");
		word+="ble";
	}
	else if(isSuffix(word, "fulli"))
	{
		word = step5(word, "fulli");
		word+="ful";
	}
	else if(isSuffix(word, "lessli"))
	{
		word = step5(word, "lessli");
		word+="less";
	}

	else if (isSuffix(word, "ogi"))
	{
		if(word.at(word.size()-4) == 'l')
		{
			word = step5(word, "ogi");
			word+="og";
		}
	}
	else if (isSuffix(word, "li"))
	{
		precede = preceder(word, "li");
		if(isValidLiEnding(precede))
		{
			word = precede;
		}
	}
		return word;
}
string WordStem::step6(string &word, string suf)
{
	if(isSuffix(word, suf))
	{
		word = word.substr(0, word.length()-suf.length());
	}
	return word;

}

string WordStem::step6(string &word){
	if(isSuffix(word, "tional"))
	{
		if (contains(Region1(word), "tional") == true)
		{
			word = step6(word, "tional");
			word += "tion";
		}
	}
	else if(isSuffix(word, "ational"))
	{
		if (contains(Region1(word), "ational") == true)
		{
			word = step6(word, "ational");
			word += "ate";
		}
	}
	else if(isSuffix(word, "alize")){
		if (contains(Region1(word), "alize") == true)
		{
			word = step6(word, "alize");
			word += "al";
		}
	}
	else if(isSuffix(word, "iciti")){
		if (contains(Region1(word), "iciti") == true)
		{
			word = step6(word, "iciti");
			word += "ic";
		}
	}
	else if(isSuffix(word, "icate")){
		if (contains(Region1(word), "icate") == true)
		{
			word = step6(word, "icate");
			word += "ic";
		}
	}
	else if(isSuffix(word, "ical")){
		if (contains(Region1(word), "ical") == true)
		{
			word = step6(word, "ical");
			word += "ic";
		}
	}
	else if(isSuffix(word, "ful")){
		if (contains(Region1(word),"ful") == true)
		{
			word = step6(word, "ful");
		}
	}
	else if(isSuffix(word, "ness")){
		if (contains(Region1(word), "ness") == true)
		{
			word = step6(word, "ness");
		}
	}
	else if(isSuffix(word, "ative")){
		if (contains(Region2(word), "ative") == true)
		{
			word = step6(word, "ative");
		}
	}
	return word;
}
string WordStem::step7(string &word, string suf)
{
	if(isSuffix(word, suf))
	{
		word = word.substr(0, word.length()-suf.length());
	}
	return word;

}

string WordStem::step7(string &word){
	if(isSuffix(word, "al"))
	{	
		if(contains(Region2(word), "al") == true)
		{
			word = step7(word, "al");

		}
	}
	else if(isSuffix(word, "ance"))
	{	
		if(contains(Region2(word),"ance") == true)
		{
			word = step7(word, "ance");

		}
	}
	else if(isSuffix(word, "ence"))
	{	
		if(contains(Region2(word),"ence") == true)
		{
			word = step7(word, "ence");

		}
	}
	else if(isSuffix(word, "er"))
	{	
		if(contains(Region2(word), "er") == true)
		{
			word = step7(word, "er");

		}
	}
	else if(isSuffix(word, "ic"))
	{	
		if(contains(Region2(word),"ic") == true)
		{
			word = step7(word, "ic");

		}
	}
	else if(isSuffix(word, "able"))
	{	
		if(contains(Region2(word), "able") == true)
		{
			word = step7(word, "able");

		}
	}
	else if(isSuffix(word, "ible"))
	{	
		if(contains(Region2(word), "ible") == true)
		{
			word = step7(word, "ible");

		}
	}
	else if(isSuffix(word, "ant"))
	{	
		if(contains(Region2(word), "ant") == true)
		{
			word = step7(word, "ant");

		}
	}
	else if(isSuffix(word, "ement"))
	{	
		if(contains(Region2(word), "ement") == true)
		{
			word = step7(word, "ement");

		}
	}
	else if(isSuffix(word, "ment"))
	{	
		if(contains(Region2(word), "ment") == true)
		{
			word = step7(word, "ment");

		}
	}
	else if(isSuffix(word, "ent"))
	{	
		if(contains(Region2(word), "ent") == true)
		{
			word = step7(word, "ent");

		}
	}
	else if(isSuffix(word, "ism"))
	{	
		if(contains(Region2(word), "ism") == true)
		{
			word = step7(word, "ism");

		}
	}
	else if(isSuffix(word, "ate"))
	{
		if(contains(Region2(word), "ate") == true)
		{
			word = step7(word, "ate");

		}
	}
	else if(isSuffix(word, "iti"))
	{	
		if(contains(Region2(word), "iti") == true)
		{
			word = step7(word, "iti");

		}
	}
	else if(isSuffix(word, "ous"))
	{	
		if(contains(Region2(word), "ous") == true)
		{
			word = step7(word, "ous");

		}
	}
	else if(isSuffix(word, "ive"))
	{	
		if(contains(Region2(word), "ive") == true)
		{
			word = step7(word, "ive");

		}
	}
	else if(isSuffix(word, "ize"))
	{	
		if(contains(Region2(word), "ize") == true)
		{
			word = step7(word, "ize");

		}
	}
	else if(isSuffix(word, "ion"))
	{	
		if(contains(Region2(word), "ion") == true)
		{
			precede = preceder(word, "ion");
			if(precede.at(precede.length()-1) == 's'
				||precede.at(precede.length()-1) == 't')
			{
				word = precede;
			}

		}
	}

	return word;
}
string WordStem::step8(string &word, string suf)
{
	if(isSuffix(word, suf))
	{
		word = word.substr(0, word.length()-suf.length());
	}
	return word;

}

string WordStem::step8(string &word){
	if (isSuffix(word, "e"))
	{
		precede = preceder(word, "e");
		if((contains(Region2(word), "e") == true) || (contains(Region1(word), "e") == true && isShortSyl(precede) == false))
		{
			word = precede;
		}
	}
	
	else if (isSuffix(word, "l"))
	{
		string ending = word.substr(word.length()-2);
		
		if(ending == "ll")
		{
			precede = preceder(word, "l");
			if(contains(Region2(word), "l"))
			{
				word = precede;
			}		
		}
		
	}
	return word;
}
