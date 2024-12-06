#include "game.h"
#include "opponentAI.h"
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

int main(int argc, char *argv[]) {
    int shipBoard[HEIGHT][WIDTH] = {0};
	int shotBoard[HEIGHT][WIDTH] = {0};
	int opponentShipBoard[HEIGHT][WIDTH] = {0};
	int opponentShotBoard[HEIGHT][WIDTH] = {0};
	Ship ships[NUM_SHIPS];
	Ship opponentShips[NUM_SHIPS];

    generateBoard(shipBoard, ships);
    drawBoard(shipBoard, shotBoard, ships, opponentShipBoard, opponentShotBoard);

    if (countShipsLeft(ships, opponentShotBoard) != NUM_SHIPS) return 16;
    if (shoot(0, 0, shipBoard, opponentShotBoard) != 1) return 1;
    if (shoot(0, 1, shipBoard, opponentShotBoard) != 1) return 2;
    if (shoot(0, 2, shipBoard, opponentShotBoard) != 1) return 3;
    if (shoot(0, 3, shipBoard, opponentShotBoard) != 0) return 4;
    if (shoot(0, 4, shipBoard, opponentShotBoard) != 0) return 5;
    if (shoot(0, 5, shipBoard, opponentShotBoard) != 0) return 6;
    if (shoot(0, 6, shipBoard, opponentShotBoard) != 0) return 7;
    if (shoot(1, 0, shipBoard, opponentShotBoard) != 1) return 9;
    if (shoot(2, 0, shipBoard, opponentShotBoard) != 1) return 10;
    if (shoot(3, 0, shipBoard, opponentShotBoard) != 1) return 11;
    if (shoot(4, 0, shipBoard, opponentShotBoard) != 1) return 12;
    if (shoot(5, 0, shipBoard, opponentShotBoard) != 0) return 13;
    if (shoot(6, 0, shipBoard, opponentShotBoard) != 0) return 14;
    if (shoot(1, 2, shipBoard, opponentShotBoard) != 1) return 15;
    drawBoard(shipBoard, shotBoard, ships, opponentShipBoard, opponentShotBoard);

    if (!isSunk(ships[0], opponentShotBoard)) return 1;
    if (isSunk(ships[1], opponentShotBoard)) return 2;
    if (!isSunk(ships[2], opponentShotBoard)) return 3;
    if (countShipsLeft(ships, opponentShotBoard) != 1) return 4;

    generateBoard(opponentShipBoard, opponentShips);
    shoot(0, 0, opponentShipBoard, shotBoard);
    shoot(8, 9, opponentShipBoard, shotBoard);
    

    drawBoard(shipBoard, shotBoard, ships, opponentShipBoard, opponentShotBoard);
}
