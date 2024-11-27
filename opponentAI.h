#include "game.h"

void opponentShoot(int *x, int *y, int difficulty, int shotBoard[][WIDTH]);
Pos *freeSpace(int shotBoard[][WIDTH], int *size);

Pos easyMode(int shotBoard[][WIDTH]);
Pos mediumMode(int shotBoard[][WIDTH]);
