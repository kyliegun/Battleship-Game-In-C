#include <stdbool.h>

#define WIDTH 10
#define HEIGHT 10

void generateBoard(int shipBoard[][WIDTH]);
void drawBoard(int shipBoard[][WIDTH], int shotBoard[][WIDTH]);

int shoot(int x, int y, int targetBoard[][WIDTH], int shotBoard[][WIDTH]);
bool isSunk(int targetBoard[][WIDTH], int shotBoard[][WIDTH]);
int countShipsLeft(int shipBoard[][WIDTH], int opponentShots[][WIDTH]);
