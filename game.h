#ifndef GAME_H
#define GAME_H

#include <stdbool.h>  //For bool, true, false

//Define the board size
#define WIDTH 10
#define HEIGHT 10
#define NUM_SHIPS 5  //Number of ships (simplified)

static const int SHIP_LENGTHS[NUM_SHIPS] = {2, 3, 3, 4, 5};

//const int SHIP_LENGTHS[] = {2, 3, 3, 4, 5};

typedef struct {
    int x;  //x position of the ship
    int y;  //y position of the ship
} Pos;

typedef struct {
    int shipID;      //the ID of the ship
    Pos headpos;     //the top-left coordinate of the ship
    int length;      //length of the ship
    bool isVertical; //if the ship is vertical or horizontal
} Ship;


//Function Declarations: 
//Generates the shipboard by placing ships on it
void generateBoard(int shipBoard[][WIDTH], int shotBoard[][WIDTH], Ship ships[], int opponentBoard[][WIDTH], int opponentShots[][WIDTH]);

//Draws both the shipBoard and shotBoard to the screen
void drawBoard(int shipBoard[][WIDTH], int shotBoard[][WIDTH], Ship ships[], int opponentBoard[][WIDTH], int opponentShots[][WIDTH]);

//Add a ship to the board
void addShip(int shipBoard[HEIGHT][WIDTH], Ship ship);

//Shoots at the given (x, y) position on the targetBoard
//Updates the shotBoard with hit (1), miss (-1), or untouched (0)
int shoot(int x, int y, int targetBoard[][WIDTH], int shotBoard[][WIDTH]);

//Checks if a specific ship with ID 'id' is sunk based on shots fired and the ship's position
bool isSunk(Ship ships, int shotBoard[][WIDTH]);

//Counts how many ships are left, based on shipBoard and shots taken
int countShipsLeft(Ship ships[], int shotBoard[][WIDTH]);

#endif //GAME_H
