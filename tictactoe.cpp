/*

   Daren Kostov
	 TicTacToe
   9/21/2022

*/
#include <iostream>

using namespace std;



void printBoard(char array[3][3]);
bool checkWin(char array[3][3], char side);
bool checkTie(char array[3][3]);

int main(){

	//make a clean board
	char board[3][3];
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			board[i][j]=' ';
		}
	}
	
	char turn='X';

	
		cout << "Welcome to Cli TicTacToe! Plece type the space coordinates you want to play. ex: 2b\n";
	
	
	printBoard(board);
	
	
	//the game loop
	while(true){
		cout << "It's " << turn << "' turn!\n";
	
		//get our input from the user
		char input[2];
		cin >> input;
	
		//translate the text based coordinates into array indexes
		int row=input[1]-'a';		
		int col=input[0]-'1';
	  
		//uncomment for debugging
		//cout << "row: " << row << ", col: " << col << endl;
		
		
		
		//if the location picked by the user is not free, including if its non-existant, reloop the loop
		if(board[row][col]!=' '){
			cout << "Space is occupied or input is wrong! Type row and then column, without punctuation or spaces. ex: 2b\n";
			continue;
		}
	
		//place the X or O on the board
		board[row][col]=turn;
	
		printBoard(board);
		
			
		//check if anyone has won or it's a tie and break out of the loop if so
		if(checkWin(board, turn)){
			cout << turn << " has won!\n";			
			break;	
		}
		else if(checkTie(board)){
			cout << turn << "Nobody won :(\n";			
			break;
		}		
			
			
		//change the next turn
		turn= turn=='O'? 'X' : 'O';
	
	}
		
		cout << "Game is starting up again...\n";
	
		main();
	
	
}

void printBoard(char array[3][3]){
	cout << "  1 2 3\n";
	cout << "a " << array[0][0] << " " << array[0][1] << " " << array[0][2] << "\n";
	cout << "  -----\n";
	cout << "b " << array[1][0] << " " << array[1][1] << " " << array[1][2] << "\n";
	cout << "  -----\n";
	cout << "c " << array[2][0] << " " << array[2][1] << " " << array[2][2] << "\n";
}

bool checkWin(char array[3][3], char side){
	  if(array[0][0]==side && array[1][0]==side && array[2][0]==side)
        return true;
    if(array[0][1]==side && array[1][1]==side && array[2][1]==side)
        return true;
    if(array[0][2]==side && array[1][2]==side && array[2][2]==side)
        return true;
    if(array[0][0]==side && array[0][1]==side && array[0][2]==side)
        return true;
    if(array[1][0]==side && array[1][1]==side && array[1][2]==side)
        return true;
    if(array[2][0]==side && array[2][1]==side && array[2][2]==side)
        return true;
    if(array[0][0]==side && array[1][1]==side && array[2][2]==side)
        return true;
    if(array[2][0]==side && array[1][1]==side && array[0][2]==side)	
				return true;
	return false;

}

bool checkTie(char array[3][3]){
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			if(array[i][j]==' '){
				return false;
			}
		}
	}
	return true;
}