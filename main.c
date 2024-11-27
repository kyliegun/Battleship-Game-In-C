#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "game.h"
#include "opponentAI.h"

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
	int shipBoard[HEIGHT][WIDTH] = {
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 2, 0},
        {0, 0, 3, 3, 6, 0, 0, 0, 2, 0},
        {0, 0, 0, 0, 6, 0, 0, 0, 2, 0},
        {0, 0, 0, 0, 4, 0, 0, 0, 2, 0},
        {0, 8, 0, 0, 4, 0, 0, 0, 2, 0},
        {0, 8, 0, 0, 4, 0, 0, 5, 0, 0},
        {0, 8, 0, 0, 4, 0, 0, 5, 0, 0},
        {0, 7, 7, 7, 7, 7, 7, 5, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
	int shotBoard[HEIGHT][WIDTH] = {0};
	int opponentShipBoard[HEIGHT][WIDTH] = {
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 2, 0},
        {0, 0, 3, 3, 6, 0, 0, 0, 2, 0},
        {0, 0, 0, 0, 6, 0, 0, 0, 2, 0},
        {0, 0, 0, 0, 4, 0, 0, 0, 2, 0},
        {0, 8, 0, 0, 4, 0, 0, 0, 2, 0},
        {0, 8, 0, 0, 4, 0, 0, 5, 0, 0},
        {0, 8, 0, 0, 4, 0, 0, 5, 0, 0},
        {0, 7, 7, 7, 7, 7, 7, 5, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
	int opponentShotBoard[HEIGHT][WIDTH] = {0};
	Ship ships[NUM_SHIPS];
	Ship opponentShips[NUM_SHIPS];

	int turn = 0;

	// generating the ship boards randomly placed
	// generateBoard(shipBoard, ships);
	// generateBoard(opponentShipBoard, opponentShips);

	int x, y;
	int xTarget;
	int yTarget;
	Pos target;
	int result;

	// main game loop
	while(1){
		if (turn == 0) {
			// drawing the boards
			drawBoard(shipBoard, shotBoard, opponentShipBoard, opponentShotBoard);
			printf("\n");

			// asking the player for cooridnates
			printf("Enter your shot (e.g., A1, B2): ");
			char rowChar;
			int col;
			scanf("%c %d" , &rowChar, &col); // reads input row and column

			// convert the row from letter to index
			int row = rowChar - 'A';

			// checking if thr shot is within bounds
			if (row < 0 || row >= HEIGHT || col < 1 || col > WIDTH){
				printf("Invalid coordinates. Please try again.\n");
				continue;
			}

			result = shoot(col - 1, row, opponentShotBoard, shotBoard);

			sleep(1);

			if(result == 0){
				printf("Missed!\n");
			}else if(result == 1){
				printf("Hit!\n");
			}else if(result == 2){
				printf("You sunk a ship!\n");
			}

			sleep(1);

			// checking if all ships are sunk
			if(countShipsLeft(ships, shotBoard) == 0){
				printf("Congratulations! You have sunk all ships.\n");
				break;
			}

			turn++;
			turn = turn % 2;
		} else {

			xTarget = 0;
			yTarget = 0;

			opponentShoot(&xTarget, &yTarget, 1, opponentShotBoard);
			printf("\n\nOpponent shoots at %c%d\n\n", yTarget+65, xTarget);

			result = shoot(xTarget, yTarget, shipBoard, opponentShotBoard);
			sleep(1);

			if(result == 0){
				printf("Missed!\n\n");
			}else if(result == 1){
				printf("Hit!\n\n");
			}else if(result == 2){
				printf("You sunk a ship!\n\n");
			}
			sleep(1);

			// checking if all ships are sunk
			if(countShipsLeft(ships, opponentShotBoard) == 0){
				printf("You have been defeated\n");
				break;
			}

			turn = (turn + 1) % 2;
		}

	}

	return 0;

}

