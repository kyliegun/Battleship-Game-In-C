#include "game.h"
#include "opponentAI.h"
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

void makeShip(int x, int y, bool vertical, int length, int ID, Ship ships[]) {
    Ship* ship = &ships[ID-1];
    ship->headpos.x = x;
    ship->headpos.y = y;
    ship->isVertical = vertical;
    ship->length = length;
    ship->shipID = ID;
}

int main(int argc, char *argv[]) {
    int shipBoard[HEIGHT][WIDTH] = {0};
	int shotBoard[HEIGHT][WIDTH] = {0};
	int opponentShipBoard[HEIGHT][WIDTH] = {0};
	int opponentShotBoard[HEIGHT][WIDTH] = {0};
	Ship ships[NUM_SHIPS];
	Ship opponentShips[NUM_SHIPS];

    makeShip(0, 0, true, 3, 1, ships);
    addShip(shipBoard, ships[0]);
    drawBoard(shipBoard, shotBoard, ships, opponentShipBoard, opponentShotBoard);
}
