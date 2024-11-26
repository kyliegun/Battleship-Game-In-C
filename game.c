#include "game.h"
#include <stdbool.h>
#include <wchar.h>
#include <locale.h>
#include <stdio.h>

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
void generateBoard(int shipBoard[][WIDTH]) {
    // add ships by modifying board
    // Initialize the shipboard with 0s (empty)
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            shipBoard[i][j] = 0;
        }
    }
}

// prints both boards to stdout
void drawBoard(int shipBoard[][WIDTH], int shotBoard[][WIDTH]) {
    setlocale(LC_ALL, "");
    // print board contents to stdout
    printf(
        "   1 2 3 4 5 6 7 8 9 10  |    1 2 3 4 5 6 7 8 9 10 \n"
        "  _____________________  |    _____________________\n");

    wchar_t boardchar;
    for (int i = 0; i < HEIGHT; i++) {
        printf("%c| ", 'A'+i);
        for (int j = 0; j < WIDTH; j++) {
            boardchar = shipBoard[i][j] ? L'■' : L'◌'; 
            printf("%lc ", boardchar);
        }


        printf("| |  %c| ", 'A'+i);
        for (int j = 0; j < WIDTH; j++) {
            switch (shotBoard[i][j]) {
                case 1:
                    boardchar = L'X';
                    break;
                case -1:
                    boardchar = L'O';
                    break;
                default:
                    boardchar = L'◌';
            };

            printf("%lc ", boardchar);
        }
        printf("|\n");
    }

    printf("  ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾  |    ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ \n");
        
}

/*
 * Shoots at position given by y, x on targetBoard.
 * Places result onto shotBoard as 1 for hit and -1 for miss.
 * Returns a 0 for miss, 1 for hit, or 2 for hit and sunk (uses isSunk for this check)
*/
int shoot(int x, int y, int targetBoard[][WIDTH], int shotBoard[][WIDTH]) {
    return 0;
}

/*
 * Checks if the ship with the given id is sunk or not by comparing the target to current hits
 * Returns true if sunk, else false
*/
bool isSunk(int id, int targetBoard[][WIDTH], int shotBoard[][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (targetBoard[i][j] > 0 && shotBoard[i][j] != 1) {
                return false; // Ship part is not hit yet
            }
        }
    }
    return true; // All parts of the ship have been hit

}

/*
 * Counts the number of ships left (maybe check isSunk on every ship id)
 * Can be used to check for a win or as output after a ship is sunk
 * Returns the number of ships remaining
*/
int countShipsLeft(int shipBoard[][WIDTH], int opponentShots[][WIDTH]) {
    return 0;
}
