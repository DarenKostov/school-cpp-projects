/*
	Daren Kostov
	Palindrome
	9/19/2022
*/
#include <iostream>
using namespace std;

int main(){
	char inputString[81];
	char processingString[81];
  int length=0;	
	char charactersWhitelist[63]="1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";

	
	cout << "Palindrome tester" << endl;
	cin.get(inputString, 81);
	cout << "your string: " << inputString << endl;
  
	// Remove all non whitelisted characters
	for(int i=0; i<81; i++){
		if(inputString[i]=='\0')
			break;
		bool acceptableCharacter=false;		
		
		for(int j=0; j<sizeof(charactersWhitelist); j++){
			if(inputString[i]==charactersWhitelist[j]){
				acceptableCharacter=true;
				continue;
			}
		}
		
		//if the character is not on the whitelist, skip it
		if(!acceptableCharacter)
			continue;
		processingString[length]=inputString[i];
		length++;
	}
	processingString[length]='\0';

	
	
	cout << length << endl;
	cout << processingString << endl;
	
	char outputString[length+1];
	
	// turn all capital letters lowercase
	for(int i=0; i<length+1; i++){
		outputString[i]=processingString[i];
		//we dont wanna check for lower case characters
		//and for the END character so we start from 36 and end with one less
		for(int j=36; j<sizeof(charactersWhitelist)-1; j++){
			if(processingString[i]==charactersWhitelist[j]){
				outputString[i]=charactersWhitelist[j-26];
				continue;
			}
		}
	}
	cout << outputString << endl;
	// check if the string is a palindrome
	for(int i=0; i<length; i++){
		if(outputString[i]!=outputString[length-i-1]){
			cout << "The inputed string is not a palindrome!" << endl;
			return 0;
		}	
	}
			cout << "The inputed string is a palindrome!" << endl;
	return 0;
}
