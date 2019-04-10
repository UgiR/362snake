#include <iostream>
#include <conio.h>
#include <chrono>
#include <windows.h>


int board[16][16];
int snake=[16][16];
	



void updateBoard(int direction, int size){
 
 Sleep(1000);
	
	
}

//1=up, 2=down,  3=left, 4=right
void move(int direction){
	
	if(direction==1){
		
		
	}
	
	
	
}

//======================================================================================end updateBorad();

//Initialize the board with all 0's
void initBoard(){
	
	//The 16x16 snake board
	for(int i=0; i<16;i++){
		
		for(int j=0;j<16;j++){
			
			board[i][j]=0;
			snake[i][j]=0;
		}
	}
	
	
}


//======================================================================================end initBoard();

//print board for debuging
void printBoard(){
	
		for(int i=0; i<16;i++){
		
		for(int j=0;j<16;j++){			
			printf("%d ", board[i][j]);
		}
		
		printf("\n");
	}
	
}







int main(){

	initBoard();
	printBoard();
	
}
