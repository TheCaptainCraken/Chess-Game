#include <stdio.h>
#include <stdlib.h>
#include "board.h"

Board InitBoard() {
    char** new_board = (char**)malloc(sizeof(char*) * BOARD_SIDE);
    if (new_board == NULL) { return NULL; }

    for (int i = 0; i < BOARD_SIDE; i++) {
        *(new_board + i) = (char*)malloc(sizeof(char) * BOARD_SIDE);
        if (*(new_board + i) == NULL) { return NULL; }
    }
    return new_board;
}


/*
*   Example of a fen string (the one representing he starting positions of all pieces)
*   rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
*   first 8 segments represent the board from top to bottom
*   then a char representing the player which has to move
*   then if castling is available
*   if en passsent is possible
*   them shit we don't care about for now.
*/
bool LoadFenString(Board board, const char* fen_string) {
    int index = 0;
    int row = 0;
    int col = 0;
    while (row < BOARD_SIDE) {
        char current = *(fen_string + index);
        if ((current >= 'A' && current <= 'Z') || (current >= 'a' && current <= 'z')) {
            *(*(board + row) + col) = current;
            col++;
        }
        else if (current == '/') {
            row++;
            col = 0;
        }
        else if (current >= '0' && current <= '9') {
            for (int i = 0; i < current - '0'; i++) {
                *(*(board + row) + col) = EMPTY;
                col++;
            }
        }
        else {
            return true;
        }
        index++;
    }
    return false;
}

void PrintBoardOnTerminal(Board board) {
    for (int row = 0; row < BOARD_SIDE; row++) {
        for (int col = 0; col < BOARD_SIDE; col++) {
            printf(" %c ", *(*(board + row) + col));
        }
        printf("\n");
    }
}
