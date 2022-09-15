/*

   Daren Kostov
   Guessing Game
   9/15/2022

1. No global variables. (Global constants are all right.)

2. No strings. Not ever. (You can use cstrings/character arrays, and the cstring and cctype libraries are okay. In fact, I recommend using strcmp and strlen in your projects.)

3. You should include <iostream>, not stdio. (This applies more to C programmers.)

4. You should avoid using a mouse when possible. Learn the shortcuts. If you ever work through a shell, you won't have a mouse available to you.
*/
#include <iostream>

using namespace std;

int main(){
	srand(time(NULL));
	while(true){
		//get random number between 0 and 100
		int number= rand()%101;
		int guesses=0;
		cout << "Guess a number between 0 and 100!" << endl;
		//get input from player
		int guess=-1;
		//loop until the player guesses correctly
		while(number!=guess){
			cin >> guess;
			guesses++;
			if(guess>number)
				cout << "less than " << guess << endl;
			else if(guess<number) 
				cout << "greater than " << guess << endl;	
		}
		//ask if the player wants to play again
		cout << "Success! Guesses: " << guesses <<" Would you like to play again? [y/n]" << endl;
		char again;
		cin >> again;
		//if yes repeat the loop if no stop the program
		switch(again){
			case 'y':
			case 'Y':
				break;
			default:
				return 0;	
		}
		cout << "playing again..." << endl;
	}


}
