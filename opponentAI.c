#include <stdio.h>
#include <stdlib.h>
#include "opponentAI.h"
#include "game.h"

// struct pos{
//     int x;
//     int y;
// };
// typedef struct pos Pos;

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

Pos easyMode(int shotBoard[][WIDTH]) {
    int size;
    Pos target;
    Pos *coordArray = freeSpace(shotBoard, &size);

    if (coordArray == NULL) {
        printf("No available shots. Something has gone wrong");
        return;
    }

    int randNum = rand() % (size + 1);
    target = *(coordArray + randNum);
    free(coordArray);
    return target;
}

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
