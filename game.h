#ifndef GAME_H
#define GAME_H

#include <stdbool.h>  //For bool, true, false

//Define the board size
#define WIDTH 10
#define HEIGHT 10
#define NUM_SHIPS 3  //Number of ships (simplified)

typedef struct {
    int col;  //x position of the ship
    int row;  //y position of the ship
} Coord;

//Function Declarations: 
//Generates the shipboard by placing ships on it
void generateBoard(int shipBoard[][WIDTH], Coord ships[]);

//Draws both the shipBoard and shotBoard to the screen
void drawBoard(int shipBoard[][WIDTH], int shotBoard[][WIDTH]); //, int opponentBoard[][WIDTH], int opponentShots[][WIDTH]); add later

//Shoots at the given (x, y) position on the targetBoard
//Updates the shotBoard with hit (1), miss (-1), or untouched (0)
int shoot(int x, int y, int targetBoard[][WIDTH], int shotBoard[][WIDTH]);

//Checks if a specific ship with ID 'id' is sunk based on shots fired and the ship's position
bool isSunk(int id, Coord ships[], int shotBoard[][WIDTH]);

//Counts how many ships are left, based on shipBoard and shots taken
int countShipsLeft(Coord ships[], int shotBoard[][WIDTH]);

#endif //GAME_H
