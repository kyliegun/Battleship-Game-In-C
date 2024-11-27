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
    Pos *coords = malloc(sizeof(struct pos) * HEIGHT*WIDTH);
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

    coords = realloc(coords, sizeof(struct pos) * n);
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
        return;
    }

    // chooses a random position within the available spaces
    int randNum = rand() % (size + 1);
    target = *(coordArray + randNum);
    free(coordArray);
    return target;
}

/**
 * @brief The medium opponent difficulty. Shoots randomly but can track hit ships
 * 
 * @param shotBoard - the 2D array of current opponent shots
 * @return Pos - The position to shoot at
 */
Pos mediumMode(int shotBoard[][WIDTH]) {
    int size;
    Pos target;
    Pos *coordArray = freeSpace(shotBoard, &size);

    if (coordArray == NULL) {
        printf("No available shots. Something has gone wrong");
        return;
    }

    // chooses a random position within the available spaces
    int randNum = rand() % (size + 1);
    target = *(coordArray + randNum);
    free(coordArray);
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
void opponentShoot(int *x, int *y, int difficulty, int shotBoard[][WIDTH]) {
    Pos target;
    switch (difficulty) {
        case 1:
            target = easyMode(shotBoard);
            *x = target.x;
            *y = target.y;
            break;
        default:
            printf("Not a valid difficulty. No shot decided");
            return;
    }
}
