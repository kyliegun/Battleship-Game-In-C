/**
 * @file opponentAI.c
 * @author Lukas Buehlmann (team 19)
 * @brief functions to simulate an opponent in battleship
 * @version v1.0.0
 * @date 2024-11-27
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "opponentAI.h"
#include "game.h"

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
                n++;
            }
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
    int hit;
    int hitCount;

    // find the max ship length
    int longestShip = 0;
    for (int i = 0;i < NUM_SHIPS;i++) {
        if (ships[i].length > longestShip) {
            longestShip = ships[i].length;
        }
    }

    Pos shipCoords[longestShip];
    Pos shipPiece;

    // loop through each ship and find coordinates of ships that are hit but not sunk
    for (int i = 0;i < NUM_SHIPS;i++) {
        ship = ships[i];
        hitCount = 0;
        
        // first copy all ship positions that are hit into shipCoord and track total hit
        for (int j = 0; j < ship.length; j++) {
            shipPiece.y = ship.headpos.y + j*ship.isVertical;
            shipPiece.x = ship.headpos.x + j*(!ship.isVertical);

            hit = shotBoard[shipPiece.y][shipPiece.x];
            if (hit == 1) {
                shipCoords[j].x = shipPiece.x;
                shipCoords[j].y = shipPiece.y;
                hitCount++;
            }
        }

        // make sure the ship is hit but not sunk and then add those values into the coords
        if (0 < hitCount && hitCount < ship.length) {
            for (int k=0;k < hitCount;k++) {
                coords[n + k] = shipCoords[k];
            }
            n += hitCount;
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

    if (coordArray == NULL) {
        printf("No available shots. Something has gone wrong");
    } else {
        // chooses a random position within the available spaces
        int randNum = rand() % (size + 1);
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
    int size;
    Pos target;
    Pos *coordArray = findHitShipCoords(shotBoard, &size, ships);

    if (size == 0 && coordArray == NULL) {
        target = easyMode(shotBoard);
        return target;
    }

    // chooses a random position within the available spaces
    int randNum = rand() % (size + 1);
    target = *(coordArray + randNum);
    free(coordArray);
    coordArray = NULL;

    // choose a random shift direction
    randNum = randNum % 4;
    switch (randNum) {
        case 0:
            // left side of target
            if (target.x > 0 && shotBoard[target.y][target.x-1] == 0) {
                target.x--;
                return target;
            }
        case 1:
            // right side of target
            if (target.x < WIDTH - 1 && shotBoard[target.y][target.x+1] == 0) {
                target.x++;
                return target;
            }
        case 2:
            // top side of target
            if (target.y > 0 && shotBoard[target.y-1][target.x] == 0) {
                target.y--;
                return target;
            }
        case 3:
            // bottom side of target
            if (target.y < HEIGHT - 1 && shotBoard[target.y+1][target.x] == 0) {
                target.y++;
                return target;
            }
        default:
            target = easyMode(shotBoard);

    }
    return target;
}

/**
 * @brief The function to manage opponent shooting
 * 
 * @param x - the intended x position to shoot at
 * @param y - the intended y position to shoot at
 * @param difficulty - the difficulty level. 1=easy
 * @param shotBoard - the 2D array representing the places that have been shot at
 */
void opponentShoot(int *x, int *y, int difficulty, int shotBoard[][WIDTH], Ship ships[]) {
    Pos target;
    switch (difficulty) {
        case 1:
            target = easyMode(shotBoard);
            *x = target.x;
            *y = target.y;
            break;
        case 2:
            target = mediumMode(shotBoard, ships);
            *x = target.x;
            *y = target.y;
            break;
        default:
            printf("Not a valid difficulty. No shot decided");
            return;
    }
}
