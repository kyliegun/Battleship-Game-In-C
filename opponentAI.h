#include "game.h"

typedef struct pos{
    int x;
    int y;
} Pos;

void opponentShoot(int *x, int *y, int difficulty, int shotBoard[][WIDTH]);
Pos *freeSpace(int shotBoard[][WIDTH], int *size);

Pos easyMode(int shotBoard[][WIDTH]);
