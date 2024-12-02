#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

/*
 * Parameter names listed here are (from perspective of the player):
 *  shipBoard[][] - your own integer array of ship positions
 *  shotBoard[][] - integer array that tracks the hits, misses, and available places to shoot
 *  targetBoard[][] - the opponents ship position array
 *  opponentShots[][] - the opponent's shotBoard
 * 
 * All arrays (so far) are modified as a side effect of the function. No arrays are returned
 * 
 * shipBoard is a 2D array that represents the board. Each ship is represented as a line of integers
 * with their own ID. For example, if there are six ships, then ship one would be the collection of
 * 1 elements, ship two as 2s, etc. Each player has one
 * 
 * shotBoard is a 2D array of integers where 0 is a spot that hasn't been tried yet, -1 is a miss, 
 * 1 is a hit. Each player has one
*/

//generates the ships on a board of dimensions HEIGHT X WIDTH (maybe define number of ships too)
// from our development plan, only has to work for a 10x10 to start
void generateBoard(int shipBoard[HEIGHT][WIDTH], Ship ships[NUM_SHIPS]) {
    // add ships by modifying board
    // prompt the player to create ship of N length
    // get input
    // either add ship at index or tell invalid spot
    // Initialize the shipboard with 0s (empty)
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            shipBoard[i][j] = 0;
        }
    }

    for (int id = 1; id <= NUM_SHIPS; id++) {
        
        Ship *ship = &ships[id];
        char row;
        int col;
        char verticality;
        
        printf("Enter the ship coordinate in the form of 'A1': ");
        scanf("%c%d", &row, &col);
        // Convert coordinate to intergers

        row -= 'A';
        col -= 1;


        printf("Do you want the ship to be verital or horizontal? (V/H): ");
        scanf("%c", &verticality);
        
        if (verticality == 'V') {
            ship->isVertical = true;
        } else if (verticality == 'H') {
            ship->isVertical = false;
        } else {
            ;
        }
        
        ship->shipID = id;
        ship->headpos.x = col;
        ship->headpos.y = row;
        ship->length = 3;

        addShip(shipBoard, *ship);
    }
}

// Helper funciton to add ships to the board based on the user input coordinates.
void addShip(int shipBoard[HEIGHT][WIDTH], Ship ship){
    for (int i = 0; i < ship.length; i++) {
        if (ship.isVertical) {
            shipBoard[ship.headpos.y + i][ship.headpos.x] = ship.shipID;
        } else {
            shipBoard[ship.headpos.y][ship.headpos.x + i] = ship.shipID;
        }
    }
}

// prints both boards to stdout
void drawBoard(int shipBoard[][WIDTH], int shotBoard[][WIDTH], int opponentBoard[][WIDTH], int opponentShots[][WIDTH]) {
    setlocale(LC_ALL, "");

    //Print column headers for both boards
    printf("   Ship Board:                 Shot Board:          \n");
    printf("   1 2 3 4 5 6 7 8 9 10  |     1 2 3 4 5 6 7 8 9 10 \n");
    printf("  _____________________  |    _____________________ \n");

    wchar_t boardChar;
    for (int i = 0; i < HEIGHT; i++) {
        //Print row labels and your shipboard (left)
        printf("%c| ", 'A' + i);
        for (int j = 0; j < WIDTH; j++) {
            if (shipBoard[i][j]) {
                if (opponentShots[i][j])    boardChar = L'□';
                else                        boardChar = L'■';
            } else {
                if (opponentShots[i][j])    boardChar = L'X';
                else                        boardChar = L'◌';
            }
            printf("%lc ", boardChar);
        }

        printf("| |  ");  //Spacer between the boards
        //Print row labels and the opponent's shotboard (right)
        printf("%c| ", 'A' + i);
        for (int j = 0; j < WIDTH; j++) {
            switch (shotBoard[i][j]) {
                case 1:
                    boardChar = L'X'; //Hit
                    break;
                case -1:
                    boardChar = L'O'; //Miss
                    break;
                default:
                    boardChar = L'◌'; //Empty (unshot)
            }
            printf("%lc ", boardChar);
        }
        printf("|\n");
    }

    //Print bottom separator line
    printf("  ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾  |    ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ \n");
}

/*
 * Shoots at position given by row, col on targetBoard.
 * Places result onto shotBoard as 1 for hit and -1 for miss.
 * Returns a 0 for miss, 1 for hit, or 2 for hit and sunk (uses isSunk for this check)
*/
int shoot(int col, int row, int targetBoard[][WIDTH], int shotBoard[][WIDTH]) {
    if (targetBoard[row][col] != 0) {
        shotBoard[row][col] = 1;  //Hit
        return 1;  
    }
    shotBoard[row][col] = -1;  //Miss
    return 0;
}

/*
 * Checks if the ship with the given id is sunk or not by comparing the target to current hits
 * Returns true if sunk, else false
*/
bool isSunk(Ship ship, int shotBoard[][WIDTH]) {
    int vertical   = ship.isVertical;
    int horizontal = !ship.isVertical;
    //Check if the shot at the ship's position has been hit
    for (int i = 0; i < ship.length; i++) {
        if (shotBoard[ship.headpos.y + i*vertical][ship.headpos.x + i*horizontal] == 0) {
            return false; //if any of the pieces are missed then the ship is not sunk
        }
    }

    return true;
}

/*
 * Counts the number of ships left (maybe check isSunk on every ship id)
 * Can be used to check for a win or as output after a ship is sunk
 * Returns the number of ships remaining
*/
int countShipsLeft(Ship ships[], int shotBoard[][WIDTH]) {
    int shipsLeft = NUM_SHIPS;
    for (int i = 1; i <= NUM_SHIPS; i++) {
        if (isSunk(ships[i], shotBoard)) {
            shipsLeft --;
        }
    }
    return shipsLeft;
}
