/**
 * @file testing.c
 * @author Connor McEachern (team 19)
 * @brief testing for game.c
 * 
 */
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
    int testboard[HEIGHT][WIDTH] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1}
    };
    int opponentTestBoard[HEIGHT][WIDTH] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0, 0, 0}
    };

	Ship ships[NUM_SHIPS];
	Ship opponentShips[NUM_SHIPS];

    generateBoard(shipBoard, shotBoard, ships, opponentShipBoard, opponentShotBoard);
    generateOpponentBoard(opponentShipBoard, opponentShips);
    drawBoard(shipBoard, shotBoard, ships, opponentShipBoard, opponentShotBoard);

    if (countShipsLeft(ships, opponentShotBoard) != NUM_SHIPS) return 5;
    for (int i = 1; i<HEIGHT; i++) {
        for (int j = 0; j<WIDTH; j++) {
            if (shoot(i, j, shipBoard, opponentShotBoard) != testboard [j][i]) return 10;
        }
    }
    drawBoard(shipBoard, shotBoard, ships, opponentShipBoard, opponentShotBoard);

    if (!isSunk(ships[0], opponentShotBoard)) return 1;
    if (isSunk(ships[1], opponentShotBoard)) return 2;
    if (!isSunk(ships[2], opponentShotBoard)) return 3;
    if (countShipsLeft(ships, opponentShotBoard) != 1) return 4;


    if (countShipsLeft(opponentShips, shotBoard) != NUM_SHIPS) return 5;
    int x, y;
    int diff;
    while (countShipsLeft(opponentShips, shotBoard) > 0) {
        opponentShoot(&x, &y, diff%4, shotBoard, opponentShips);
        if (diff != 0 && shoot(x, y, opponentShipBoard, shotBoard) != opponentTestBoard[y][x]) return 11;
        diff++;
    }
    
    drawBoard(shipBoard, shotBoard, ships, opponentShipBoard, opponentShotBoard);
}
