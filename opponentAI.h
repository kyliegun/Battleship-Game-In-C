#include "game.h"

void generateOpponentBoard(int shipBoard[][WIDTH], Ship ships[]);
bool isShipValid(Ship ship, int shipBoard[][WIDTH]);

void opponentShoot(int *x, int *y, int difficulty, int shotBoard[][WIDTH], Ship ships[]);
Pos *freeSpace(int shotBoard[][WIDTH], int *size);
Pos *findHitShipCoords(int shotBoard[][WIDTH], int *size, Ship ships[]);

Pos easyMode(int shotBoard[][WIDTH]);
Pos mediumMode(int shotBoard[][WIDTH], Ship ships[]);
