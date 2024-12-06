#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "game.h"
#include "opponentAI.h"

// #define DEBUG


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

// handle flags given at startup. -1 for no actions, 0 for help printed, 1 for invalid input
int flagHandler(int argc, char* argv[]) {
	if (argc > 1){
		for (int i = 1; i < argc; i++){
			if (strcmp(argv[i], "--help") == 0){
				displayHelp();
				return 0;
			}else if (strcmp(argv[i], "--play") == 0){
				printf("Game is starting!");
				return -1;
			}else{
				printf("Invalid argument: %s\n", argv[i]);
				printf("Please use --help to view options.\n");
				return 1;
			}
		}
	}
	return -1;
}

// helper function to get the user's desired target coordinates
Pos getUserTarget() {
	Pos target;
	char rowChar;

	while (1) {
		printf("\nEnter your shot (e.g., A1, B2): ");
		if (!scanf(" %c %d" , &rowChar, &target.x)) {
			scanf(" %*c");
			printf("Invalid input. Please enter a valid letter and number\n\n");
			continue;
		}

		// subtract ASCII 'A' val to map to a number from 0 to 9
		rowChar = tolower(rowChar);
		target.y = rowChar - 'a';

		// subtract 1 from x to map to width of list indices
		target.x--;

		if (target.y < 0 || target.y >= HEIGHT || target.x < 0 || target.x >= WIDTH) {
			printf("Invalid coordinates. Please try again.\n");
			continue;
		}
		break;

	}

	return target;
}

// provides some user output and returns whether a ship is hit or not
bool analyseResult(int result, int targetVal, Ship ships[], int shotBoard[][WIDTH]) {
	bool hit = false;
	if (result) {
		if (isSunk(ships[targetVal-1], shotBoard)) {
			puts("Hit and sunk!");
		} else {
			puts("Hit!");
		}
		hit = true;
	} else {
		puts("Missed!");
	}
	return hit;
}

int main(int argc, char *argv[]) {
	switch(flagHandler(argc, argv)) {
		case 0:
			return EXIT_SUCCESS;
			break;
		case 1:
			return EXIT_FAILURE;
			break;
	}

	// initialise all player and opponent information
	int shipBoard[HEIGHT][WIDTH] = {0};
	int shotBoard[HEIGHT][WIDTH] = {0};
	int opponentShipBoard[HEIGHT][WIDTH] = {0};
	int opponentShotBoard[HEIGHT][WIDTH] = {0};
	Ship ships[NUM_SHIPS];
	Ship opponentShips[NUM_SHIPS];

	int turn = 0;
	int difficulty;
	
	int xTarget;
	int yTarget;
	Pos target;
	int result;
	
	#ifndef DEBUG
		difficulty = 1;
	#endif
	#ifndef DEBUG
		difficulty = chooseOpponentDifficulty();
	#endif

	// generating both players ship boards
	generateBoard(shipBoard, shotBoard, ships, opponentShipBoard, opponentShotBoard);
	generateOpponentBoard(opponentShipBoard, opponentShips);
	drawBoard(shipBoard, shotBoard, ships, opponentShipBoard, opponentShotBoard);

	// main game loop
	while(1) {

		// player turn
		if (!turn) {
			drawBoard(shipBoard, shotBoard, ships, opponentShipBoard, opponentShotBoard);

			// get user input to shoot at a target location
			target = getUserTarget();
			result = shoot(target.x, target.y, opponentShipBoard, shotBoard);
			#ifndef DEBUG 
			sleep(1);
			#endif

			// print output relating to result
			if (!analyseResult(result, opponentShipBoard[target.y][target.x], opponentShips, shotBoard)) {
				turn = (turn+1) % 2;
			}
			#ifndef DEBUG 
			sleep(1);
			#endif
			
			// checking if all ships are sunk
			if(countShipsLeft(opponentShips, shotBoard) == 0){
				printf("Congratulations! You have sunk all ships.\n");
				break;
			}
		} else {

			opponentShoot(&xTarget, &yTarget, difficulty, opponentShotBoard, ships);
			printf("\n\nOpponent shoots at %c%d\n\n", yTarget+65, xTarget+1);

			result = shoot(xTarget, yTarget, shipBoard, opponentShotBoard);
			#ifndef DEBUG 
			sleep(1);
			#endif

			// print output relating to result
			if (!analyseResult(result, shipBoard[yTarget][xTarget], ships, opponentShotBoard)) {
				turn = (turn+1) % 2;
			}
			
			// checking if all ships are sunk
			if(countShipsLeft(ships, opponentShotBoard) == 0){
				printf("You have been defeated\n");
				break;
			}
		}

	}

	printf("Your Boards\n");
	drawBoard(shipBoard, shotBoard, ships, opponentShipBoard, opponentShotBoard);
	printf("\nYour opponents Boards\n");
	drawBoard(opponentShipBoard, opponentShotBoard, opponentShips, shipBoard, shotBoard);

	return 0;

}

