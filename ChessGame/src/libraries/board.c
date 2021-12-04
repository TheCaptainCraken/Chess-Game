#include "../../dependencies/include/raylib.h"
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

void PrintBoard(Board board, Texture2D* textures) {
    int step = GetScreenHeight() / BOARD_SIDE;
    int start = (GetScreenWidth() - (step * 8)) / 2;

    for (int row = 0; row < BOARD_SIDE; row++) {
        for (int col = 0; col < BOARD_SIDE; col++) {
            DrawRectangle((col * step) + start, row * step, step, step, (row + col) % 2 == 0 ? ORANGE : YELLOW);
            if (*(*(board + row) + col) != ' ') {
                switch (*(*(board + row) + col)) {
                case 'b':
                    DrawTexture(textures[0], (col * step) + start, row * step, WHITE);
                    break;
                case 'k':
                    DrawTexture(textures[1], (col * step) + start, row * step, WHITE);
                    break;
                case 'n':
                    DrawTexture(textures[2], (col * step) + start, row * step, WHITE);
                    break;
                case 'p':
                    DrawTexture(textures[3], (col * step) + start, row * step, WHITE);
                    break;
                case 'q':
                    DrawTexture(textures[4], (col * step) + start, row * step, WHITE);
                    break;
                case 'r':
                    DrawTexture(textures[5], (col * step) + start, row * step, WHITE);
                    break;
                case 'B':
                    DrawTexture(textures[6], (col * step) + start, row * step, WHITE);
                    break;
                case 'K':
                    DrawTexture(textures[7], (col * step) + start, row * step, WHITE);
                    break;
                case 'N':
                    DrawTexture(textures[8], (col * step) + start, row * step, WHITE);
                    break;
                case 'P':
                    DrawTexture(textures[9], (col * step) + start, row * step, WHITE);
                    break;
                case 'Q':
                    DrawTexture(textures[10], (col * step) + start, row * step, WHITE);
                    break;
                case 'R':
                    DrawTexture(textures[11], (col * step) + start, row * step, WHITE);
                    break;
                default:
                    printf("Error Unknown Piece");
                }
            }
        }
    }

}

void DestroyBoard(Board board) {
    for (int i = 0; i < BOARD_SIDE; i++) {
        free(*(board + i));
    }
    free(board);
}
