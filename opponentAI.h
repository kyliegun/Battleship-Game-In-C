#include "game.h"

// creates a randomly generated board for the opponent
void generateOpponentBoard(int shipBoard[][WIDTH], Ship ships[]);

// checks if a given ship can be placed in the board without any overlap of existing ships
bool isShipValid(Ship ship, int shipBoard[][WIDTH]);
int chooseOpponentDifficulty();

// prompts to let user chooes the difficulty level of the opponent
int chooseOpponentDifficulty();


// function to call to get the opponent's intended target. x and y are the target coordinates modified as side effect
void opponentShoot(int *x, int *y, int difficulty, int shotBoard[][WIDTH], Ship playerShips[]);

// finds the coordinates of every space that hasn't been shot at yet
Pos *freeSpace(int shotBoard[][WIDTH], int *size);

// finds the coordinates of every point that is part of a ship that has been hit but not sunk
Pos *findHitShipCoords(int shotBoard[][WIDTH], int *size, Ship ships[]);


// the easiest difficulty. Shoots randomly
Pos easyMode(int shotBoard[][WIDTH]);

// Tries to finish off ships if possible but otherwise shoots randomly
Pos mediumMode(int shotBoard[][WIDTH], Ship ships[]);

// Tries to finish off ships if possible, otherwise shoots at every other cell
Pos hardMode(int shotBoard[][WIDTH], Ship ships[]);
