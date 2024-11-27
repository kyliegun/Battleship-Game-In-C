#include <stdio.h>
#include <stdlib.h>
#include "game.h"

// function to display help message
void displayHelp() {
    printf("Welcome to Sinking Ships!\n");
    printf("Usage:\n");
    printf("  --help       Display this help message\n");
    printf("  --play       Start a new game\n");
    printf("\nGame Instructions:\n");
    printf("1. The game board is 10x10, where you have to sink all the opponent's ships.\n");
    printf("2. You will be prompted to enter coordinates (e.g., A1, B2) to shoot at.\n");
    printf("3. You will receive feedback if you hit, miss, or sink a ship.\n");
    printf("4. The game ends when all ships are sunk.\n");
    printf("\nOptions:\n");
    printf("  --help      Show this help message\n");
    printf("  --play      Start a new game\n");
    printf("\nGood luck!\n");
}


int main() {
	int shipBoard[HEIGHT][WIDTH];
	int shotBoard[HEIGHT][WIDTH] = {0};

	// generating the ship boards randomly placed
	generateBoard(shipBoard);

	int x, y;
	int result;

	// main game loop
	while(1){
		// drawing the boards
		printf("Ship Board:\n");
		drawBoard(shipBoard, shotBoard);
		printf("\n");

		// asking the player for cooridnates
		printf("Enter your shot (e.g., A1, B2): ");
		char rowChar;
		int col;
		scanf("%c %d, &rowChar, &col"); // reads input row and column

		// convert the row from letter to index
		int row = rowChar - 'A';

		// checking if thr shot is within bounds
		if (row < 0 || row >= HEIGHT || col < 1 || col > WIDTH){
			printf("Invalid coordinates. Please try again.\n");
			continue;
		}

		result = shoot(col - 1, row, shipBoard, shotBoard);

		if(result == 0){
			printf("Missed!\n");
		}else if(result == 1){
			printf("Hit!\n");
		}else if(result == 2){
			printf("You sunk a ship!\n");
		}

		// checking if all ships are sunk
		if(countShipsLeft(shipBoard, shotBoard) == 0){
			printf("Congratulations! You have sunk all ships.\n");
			break;
		}

	}

	return 0;

}

