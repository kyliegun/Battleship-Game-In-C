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
void generateBoard(int shipBoard[][WIDTH], Ship ships[]) {
    // add ships by modifying board
    // Initialize the shipboard with 0s (empty)
    for (int i = 0; i < NUM_SHIPS; i++) {
        int x = rand() % WIDTH;
        int y = rand() % HEIGHT;
        shipBoard[y][x] = 1;  //Mark ship on the board

        //Store ship position for checking sunk status later
        ships[i].x = x;
        ships[i].y = y;
    }
}

// prints both boards to stdout
void drawBoard(int shipBoard[][WIDTH], int shotBoard[][WIDTH]) { //, int opponentBoard[][WIDTH], int opponentShots[][WIDTH]) { add later
    setlocale(LC_ALL, "");

    //Print column headers for both boards
    printf("   1 2 3 4 5 6 7 8 9 10  |     1 2 3 4 5 6 7 8 9 10 \n");
    printf("  _____________________  |    _____________________ \n");

    wchar_t boardChar;
    for (int i = 0; i < HEIGHT; i++) {
        //Print row labels and your shipboard (left)
        printf("%c| ", 'A' + i);
        for (int j = 0; j < WIDTH; j++) {
            boardChar = shipBoard[i][j] ? L'▲' : L'◌';  //Ship or empty
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
 * Shoots at position given by y, x on targetBoard.
 * Places result onto shotBoard as 1 for hit and -1 for miss.
 * Returns a 0 for miss, 1 for hit, or 2 for hit and sunk (uses isSunk for this check)
*/
int shoot(int x, int y, int targetBoard[][WIDTH], int shotBoard[][WIDTH]) {
    if (targetBoard[y][x] != 0) {
        shotBoard[y][x] = 1;  //Hit
        return 1;  
    }
    shotBoard[y][x] = -1;  //Miss
    return 0;
}

/*
 * Checks if the ship with the given id is sunk or not by comparing the target to current hits
 * Returns true if sunk, else false
*/
bool isSunk(int id, Ship ships[], int shotBoard[][WIDTH]) {
    //Check if the shot at the ship's position has been hit
    return shotBoard[ships[id].y][ships[id].x] == 1;
}

/*
 * Counts the number of ships left (maybe check isSunk on every ship id)
 * Can be used to check for a win or as output after a ship is sunk
 * Returns the number of ships remaining
*/
int countShipsLeft(Ship ships[], int shotBoard[][WIDTH]) {
    int shipsLeft = 0;
    for (int i = 0; i < NUM_SHIPS; i++) {
        if (shotBoard[ships[i].y][ships[i].x] != 1) {
            shipsLeft++;
        }
    }
    return shipsLeft;
}
