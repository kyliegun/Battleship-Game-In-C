#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <ctype.h>

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

/* Generates the ships on a board of dimensions HEIGHT X WIDTH.
 * Prompt the user to enter where they want to place the ship and its direction.
 */
void generateBoard(int shipBoard[HEIGHT][WIDTH], Ship ships[NUM_SHIPS]) {

    printf("\n\tIt's time to place your ship!\n");

    // User interface to get a valid coordinate and verticality. Then add the ships to shipBoard
    for (int id = 1; id <= NUM_SHIPS; id++) {
        
        // Instantiate known ship attributes
        Ship *ship = &ships[id - 1];
        ship->shipID = id;
        ship->length = SHIP_LENGTHS[id - 1];
        
        // Instantiate user input and flag variables
        char row;
        int col;
        char verticality;
        bool validInput = false; // for the do-while loop so it only exits after validating the inputs

        // Get ship start position from the user and make sure it is within the range and is empty
        do {
            printf("\n***Keep in mind that the ship can ONLY EXTEND TO THE RIGHT OR DOWNWARDS***\n");
            printf("\t[Ship #%d | Ship length: %d]\n", id, ship->length);
            printf("Enter the start position of the ship (A1-J10): ");
            scanf(" %c%d", &row, &col);

            // Convert coordinates to correct array indices
            row = tolower(row);
            row -= 'a';
            col -= 1;

            // Check if the user input is within the board and the position is empty(0)
            if (row < 0 || row >= WIDTH || col < 0 || col >= HEIGHT) {
                printf("\n!!!Please enter a coordinate within the board!!!\n\n");
                continue;
            }
            else if (shipBoard[row][col] != 0) {
                printf("\n!!!There's already a ship here. Please try again!!!\n\n");
                continue;
            }
            
        // Get the verticality of the ship from the user and make sure it won't extend out of bounds and does not overlap other ships
            printf("\nDo you want the ship to be verital or horizontal? (v/h): ");
            scanf(" %c", &verticality);
            
            verticality = tolower(verticality);

            // Check if the ship can be placed vertically and set the validInput flag to true if so.
            // Otherwise, validInput is set to false
            if (verticality == 'v' && ((col + ship->length) < HEIGHT) ) {
                
                // Check for overlaps
                for (int i = 1; i < ship->length; i++) {
                    if (shipBoard[row][col + i] != 0){
                        printf("\n!!!There is a ship in the way. Please pick another starting position or direction!!!\n\n");
                        validInput = false;
                        break;
                    }
                    else {
                        validInput = true;
                        ship->isVertical = true;
                    }
                }
            }
            // Check if the ship can be placed horizontally and set the validInput flag to true if so.
            // Otherwise, validInput is set to false
            else if (verticality == 'h' && ((row + ship->length) < WIDTH) ) {

                //Check for overlaps
                for (int i = 1; i < ship->length; i++) {
                    if (shipBoard[row + i][col] != 0){
                        printf("\n!!!There is a ship in the way. Please pick another starting position or direction!!!\n\n");
                        validInput = false;
                        break;
                    }
                    else {
                        validInput = true;
                        ship->isVertical = false;
                    }
                }
            }
            else { // If previous conditions fail, then the user would have to pick a new starting position
                printf("\n!!!Cannot placed the ship either vertically or horizontally. Pick a new starting position!!!\n\n");
                continue;
            }

        } while (!validInput); // Continuously prompt the user till all the inputs are valid.
        
        // Instantiate the ship head positions after validation
        ship->headpos.x = col;
        ship->headpos.y = row;

        // Place the ship in the shipBoard array
        addShip(shipBoard, *ship);
        printf("\n✔ Ship #%d placed successfully! ✔\n\n", id);
    }
}

// Helper funciton to add ships to the board based on the user input coordinates.
void addShip(int shipBoard[HEIGHT][WIDTH], Ship ship){

    // Add ship to the shipBoard array
    for (int i = 0; i < ship.length; i++) {
        if (ship.isVertical) {
            shipBoard[ship.headpos.y + i][ship.headpos.x] = ship.shipID;
        } else {
            shipBoard[ship.headpos.y][ship.headpos.x + i] = ship.shipID;
        }
    }
}

/*
 * Draws the shipBoard and shotBoard to stdout.
 * Uses Unicode characters to create the ships.
*/
void drawBoard(int shipBoard[][WIDTH], int shotBoard[][WIDTH], Ship ships[], int opponentBoard[][WIDTH], int opponentShots[][WIDTH]) {
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
            int shipID;
            if (shipID = shipBoard[i][j]) { //Test if there is a ship and save the shipID
                Ship ship = ships[shipID-1];
                Pos tailpos; //Find the tail position of the ship
                
                tailpos.x = ship.headpos.x + (ship.length-1) * !ship.isVertical;
                tailpos.y = ship.headpos.y + (ship.length-1) * ship.isVertical;

                if (ship.headpos.y == i && ship.headpos.x == j) {
                    if (opponentShots[i][j])    boardChar = ship.isVertical ? L'△' : L'◁'; //Front has been hit
                    else                        boardChar = ship.isVertical ? L'▲' : L'◀'; //Front has not been hit
                } else if (tailpos.y == i && tailpos.x == j) {
                    if (opponentShots[i][j])    boardChar = ship.isVertical ? L'▽' : L'▷'; //Back has been hit
                    else                        boardChar = ship.isVertical ? L'▼' : L'▶'; //Back has not been hit
                } else {
                    if (opponentShots[i][j])    boardChar = L'□'; //Ship has been hit
                    else                        boardChar = L'■'; //Ship has not been hit
                }
                
            } else {
                if (opponentShots[i][j])    boardChar = L'X'; //Miss shot
                else                        boardChar = L'◌'; //Empty 
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
 * Returns a 0 for miss or 1 for hit
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

bool isAllSunk(Ship ships[], int opponentShots[][WIDTH]) {
    int result = 1;
    for (int i=0;i < NUM_SHIPS;i++) {
        result *= isSunk(ships[i], opponentShots);
    }
    return result;
}

/*
 * Counts the number of ships left (maybe check isSunk on every ship id)
 * Can be used to check for a win or as output after a ship is sunk
 * Returns the number of ships remaining
*/
int countShipsLeft(Ship ships[], int shotBoard[][WIDTH]) {
    int shipsLeft = NUM_SHIPS;
    for (int i = 0; i < NUM_SHIPS; i++) {
        if (isSunk(ships[i], shotBoard)) {
            shipsLeft --;
        }
    }
    return shipsLeft;
}
