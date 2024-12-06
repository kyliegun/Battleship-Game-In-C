/**
 * @file opponentAI.c
 * @brief functions to simulate an opponent in battleship
 * @version v1.0.0
 * @date 2024-11-27
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "opponentAI.h"

/**
 * @brief generates a randomized board for the opponent
 * 
 * @param shipBoard the 2D int array representing the opponent ship positions
 * @param ships the collection of opponent ships
 */
void generateOpponentBoard(int shipBoard[][WIDTH], Ship ships[]) {
    int placed = 0;
    int randX = 0;
    int randY = 0;
    int verticality = 0;
    int n = 0;

    Ship *ship;

    // random seed is set to the current time to be different each runtime or 1 on debug
    #ifdef DEBUG
        srand(1);
    #endif
    #ifndef DEBUG
        srand(time(NULL));
    #endif

    // loops until all ships are placed
    while (placed < NUM_SHIPS) {
        ship = &ships[placed];

        // first generates a random position and orientation within the possible starting points
        verticality = rand() % 2;
        randX = rand() % (WIDTH - !verticality*SHIP_LENGTHS[placed]);
        randY = rand() % (HEIGHT - verticality*SHIP_LENGTHS[placed]);

        // create the ship definition
        ship->shipID = placed+1;
        ship->headpos.x = randX;
        ship->headpos.y = randY;
        ship->isVertical = verticality;
        ship->length = SHIP_LENGTHS[placed];

        // make sure the ship is not intersecting another before placing it
        if (isShipValid(*ship, shipBoard)) {
            addShip(shipBoard, *ship);
            placed++;
        }
    }
}

/**
 * @brief checks to see if a given ship can be placed in the board without overlap
 * Does not check for out of array bounds
 * 
 * @param ship The ship struct to place
 * @param shipBoard the board to place it into
 * @return true if the ship can be placed
 * @return false if there is an intersection in the board
 */
bool isShipValid(Ship ship, int shipBoard[][WIDTH]) {
    for (int i=0;i < ship.length;i++) {
        if (shipBoard[ship.headpos.y + i*ship.isVertical][ship.headpos.x + i*!ship.isVertical] != 0) {
            return false;
        }
    }
    return true;
}

/**
 * @brief a brief section of user prompts to get input for difficulty level
 * 
 * @return int - the chosen difficulty
 */
int chooseOpponentDifficulty() {
    int val;

    while(1) {
        printf("\nPlease enter an opponent difficulty: \n");
        printf("\t1 - easy    2 - medium    3 - hard\n");

        if (scanf(" %d", &val) == 0) {
            scanf(" %*c");
            printf("Bad input. Make sure you enter either a 1, 2, or 3\n");
            continue;
        } else if (val <= 0 || val > 3) {
            printf("Bad input. Make sure you enter either a 1, 2, or 3\n");
            continue;
        }

        printf("Difficulty %d chosen\n\n", val);

        return val;
    }
}

/**
 * @brief Finds all 0 elements of a 2D array and returns an array of position values(x, y)
 * 
 * @param shotBoard - The board to check for empty spaces
 * @param size - the size of the array to be modified as side effect
 * @return Pos* - an array of positions
 */
Pos *freeSpace(int shotBoard[][WIDTH], int *size) {
    Pos *coords = malloc(sizeof(Pos) * HEIGHT*WIDTH);
    int n = 0;

    for (int i=0;i < HEIGHT;i++) {
        for (int j=0;j < WIDTH;j++) {
            if (shotBoard[i][j] == 0) {
                (coords + n) -> x = j;
                (coords + n) -> y = i;
                // printf("x: %d, y: %d\n", j, i);
                n++;
            }
            // printf("x: %d, y: %d, val: %d\n", j, i, shotBoard[i][j]);
        }
    }

    coords = realloc(coords, sizeof(Pos) * n);
    *size = n;
    return coords;
}

/**
 * @brief finds all ship positions that have been hit but that ship is not sunk yet
 * 
 * @param shotBoard the opponent's collection of shots as a 2D int array
 * @param size the size of the returned array to be modified as side effect
 * @param ships the collection of the player's ships
 * @return Pos* an array of positions that are hit
 */
Pos *findHitShipCoords(int shotBoard[][WIDTH], int *size, Ship ships[]) {

    // allocate space for return
    Pos *coords = malloc(sizeof(Pos) * HEIGHT*WIDTH);
    if (coords == NULL) {
        return NULL;
    }

    bool shipSunk;
    int n = 0;
    Ship ship;
    Pos shipPiece;

    // find the max ship length
    int longestShip = 0;
    for (int i = 0;i < NUM_SHIPS;i++) {
        if (ships[i].length > longestShip) {
            longestShip = ships[i].length;
        }
    }

    // loop through each ship and find coordinates of ships that are hit but not sunk
    for (int i = 0;i < NUM_SHIPS;i++) {
        ship = ships[i];

        if (isSunk(ship, shotBoard)) {
            continue;
        }
        
        // first copy all ship positions that are hit into shipCoord and track total hit
        for (int j = 0; j < ship.length; j++) {
            shipPiece.y = ship.headpos.y + j*ship.isVertical;
            shipPiece.x = ship.headpos.x + j*(!ship.isVertical);

            if (shotBoard[shipPiece.y][shipPiece.x] == 1) {
                (coords+n) -> x = shipPiece.x;
                (coords+n) -> y = shipPiece.y;
                n++;
            }
        }
    }

    coords = realloc(coords, sizeof(Pos) * n);
    *size = n;
    return coords;
}

/**
 * @brief The easiest opponent difficulty. Shoots completely randomly
 * 
 * @param shotBoard - the 2D array of current opponent shots
 * @return Pos - The position to shoot at
 */
Pos easyMode(int shotBoard[][WIDTH]) {
    int size;
    Pos target;
    Pos *coordArray = freeSpace(shotBoard, &size);
    // printf("size of options: %d\n", size);

    if (coordArray == NULL) {
        printf("No available shots. Something has gone wrong");
    } else {
        // chooses a random position within the available spaces
        int randNum = rand() % (size);
        target = *(coordArray + randNum);
        free(coordArray);
        return target;
    }
}

/**
 * @brief The medium opponent difficulty. Shoots randomly but can track hit ships
 * 
 * @param shotBoard - the 2D array of current opponent shots
 * @return Pos - The position to shoot at
 */
Pos mediumMode(int shotBoard[][WIDTH], Ship ships[]) {
    int size = 0;
    Pos target;
    Pos *coordArray = findHitShipCoords(shotBoard, &size, ships);

    if (size == 0 && coordArray == NULL) {
        target = easyMode(shotBoard);
        return target;
    }

    // chooses a random position within the available spaces
    int randNum = rand() % size;
    target = *(coordArray + randNum);
    free(coordArray);
    coordArray = NULL;

    // left side of target
    if (target.x > 0 && (shotBoard[target.y][target.x-1] == 0)) {
        target.x--;
        return target;
    }

    // right side of target
    if (target.x < WIDTH - 1 && (shotBoard[target.y][target.x+1] == 0)) {
        target.x++;
        return target;
    }

    // top side of target
    if (target.y > 0 && (shotBoard[target.y-1][target.x] == 0)) {
        target.y--;
        return target;
    }

    // bottom side of target
    if (target.y < HEIGHT - 1 && (shotBoard[target.y+1][target.x] == 0)) {
        target.y++;
        return target;
    }

    target = easyMode(shotBoard);

    return target;
}


/**
 * @brief The hard opponent difficulty. Shoots at every other cell and can track hit ships
 * 
 * @param shotBoard - the 2D array of current opponent shots
 * @return Pos - The position to shoot at
 */
Pos hardMode(int shotBoard[][WIDTH], Ship ships[]) {
    int size = 0;
    Pos target;
    Pos *coordArray = findHitShipCoords(shotBoard, &size, ships);

    // create a shotboard replica where every other cell is a 1
    // This tricks the easyMode function into only shooting at every other cell
    int fakeShotBoard[HEIGHT][WIDTH] = {0};
    for (int i=0;i < HEIGHT;i++) {
        for (int j=0;j < WIDTH;j++) {
            if ((i + j) % 2 == 0) {
                fakeShotBoard[i][j] = shotBoard[i][j];
            } else {
                fakeShotBoard[i][j] = 1;
            }
        }
    }

    if (size == 0 && coordArray == NULL) {
        target = easyMode(fakeShotBoard);
        return target;
    }

    // chooses a random position within the available spaces
    int randNum = rand() % size;
    target = *(coordArray + randNum);
    free(coordArray);
    coordArray = NULL;

    // left side of target
    if (target.x > 0 && (shotBoard[target.y][target.x-1] == 0)) {
        target.x--;
        return target;
    }

    // right side of target
    if (target.x < WIDTH - 1 && (shotBoard[target.y][target.x+1] == 0)) {
        target.x++;
        return target;
    }

    // top side of target
    if (target.y > 0 && (shotBoard[target.y-1][target.x] == 0)) {
        target.y--;
        return target;
    }

    // bottom side of target
    if (target.y < HEIGHT - 1 && (shotBoard[target.y+1][target.x] == 0)) {
        target.y++;
        return target;
    }

    target = easyMode(fakeShotBoard);

    return target;
}

/**
 * @brief The function to manage opponent shooting
 * 
 * @param x - the intended x position to shoot at
 * @param y - the intended y position to shoot at
 * @param difficulty - the difficulty level. 1=easy
 * @param shotBoard - the 2D array representing the places that have been shot at
 * @param playerShips - an array of the player's ships
 */
void opponentShoot(int *x, int *y, int difficulty, int shotBoard[][WIDTH], Ship playerShips[]) {
    Pos target;
    switch (difficulty) {
        case 1:
            target = easyMode(shotBoard);
            *x = target.x;
            *y = target.y;
            break;
        case 2:
            target = mediumMode(shotBoard, playerShips);
            *x = target.x;
            *y = target.y;
            break;
        case 3:
            target = hardMode(shotBoard, playerShips);
            *x = target.x;
            *y = target.y;
            break;
        default:
            printf("Not a valid difficulty. No shot decided");
            return;
    }
}
