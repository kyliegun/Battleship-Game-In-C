#include <stdio.h>
#include <stdlib.h>
#include "game.h"

struct pos{
    int x;
    int y;
};
typedef struct pos Pos;

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

void easyMode(int *x, int *y, int shotBoard[][WIDTH]) {
    int size;
    Pos *coordArray = freeSpace(shotBoard, &size);

    if (coordArray == NULL) {
        printf("No available shots. Something has gone wrong");
        return;
    }

    int randNum = (int)(rand() * size);
    *x = (*(coordArray + randNum)).x;
    *y = (*(coordArray + randNum)).y;
    free(coordArray);
}

void opponentShoot(int *x, int *y, int difficulty, int shotBoard[][WIDTH]) {
    x = NULL;
    y = NULL;
    switch (difficulty) {
        case 1:
            easyMode(x, y, shotBoard);
            break;
        default:
            printf("Not a valid difficulty. No shot decided");
            return;
    }
}
