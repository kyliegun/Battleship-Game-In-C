#include "game.h"

struct pos{
    int x;
    int y;
};
typedef struct pos Pos;

void opponentShoot(int *x, int *y, int difficulty, int shotBoard[][WIDTH]);
Pos *freeSpace(int shotBoard[][WIDTH], int *size);

void easyMode(int *x, int *y, int shotBoard[][WIDTH]);
