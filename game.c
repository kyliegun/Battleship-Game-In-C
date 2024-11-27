#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

void generateBoard(int shipBoard[][WIDTH], Ship ships[]) {
    //Place ships at random positions
    for (int i = 0; i < NUM_SHIPS; i++) {
        int x = rand() % WIDTH;
        int y = rand() % HEIGHT;
        shipBoard[y][x] = 1;  //Mark ship on the board

        //Store ship position for checking sunk status later
        ships[i].x = x;
        ships[i].y = y;
    }
}

void drawBoard(int shipBoard[][WIDTH], int shotBoard[][WIDTH], int opponentBoard[][WIDTH], int opponentShots[][WIDTH]) {
    setlocale(LC_ALL, "");

    //Print column headers for both boards
    printf("   1 2 3 4 5 6 7 8 9 10  |    1 2 3 4 5 6 7 8 9 10 \n");
    printf("  _____________________  |    _____________________\n");

    wchar_t boardChar;
    for (int i = 0; i < HEIGHT; i++) {
        //Print row labels and your shipboard (left)
        printf("%c| ", 'A' + i);
        for (int j = 0; j < WIDTH; j++) {
            boardChar = shipBoard[i][j] ? L'■' : L'◌';  //Ship or empty
            printf("%lc ", boardChar);
        }

        printf("| |  ");  //Spacer between the boards
        //Print row labels and the opponent's shotboard (right)
        printf("%c| ", 'A' + i);
        for (int j = 0; j < WIDTH; j++) {
            switch (opponentShots[i][j]) {
                case 1:
                    boardChar = L'X'; //Hit
                    break;
                case -1:
                    boardChar = L'O'; //Miss
                    break;
                default:
                    boardChar = L'◌'; //Empty (unshot)
            }
            printf("%lc ", boardChar);
        }
        printf("|\n");
    }

    //Print bottom separator line
    printf("  ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾  |    ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ \n");
}

int shoot(int x, int y, int targetBoard[][WIDTH], int shotBoard[][WIDTH]) {
    if (targetBoard[y][x] != 0) {
        shotBoard[y][x] = 1;  //Hit
        return 1;  
    }
    shotBoard[y][x] = -1;  //Miss
    return 0;
}

bool isSunk(int id, Ship ships[], int shotBoard[][WIDTH]) {
    //Check if the shot at the ship's position has been hit
    return shotBoard[ships[id].y][ships[id].x] == 1;
}

int countShipsLeft(Ship ships[], int shotBoard[][WIDTH]) {
    int shipsLeft = 0;
    for (int i = 0; i < NUM_SHIPS; i++) {
        if (shotBoard[ships[i].y][ships[i].x] != 1) {
            shipsLeft++;
        }
    }
    return shipsLeft;
}
