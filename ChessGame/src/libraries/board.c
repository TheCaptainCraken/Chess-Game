#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIDE 8
#define EMPTY ' '
#define WHITE_PAWN 'P'
#define WHITE_KNIGHT 'N'
#define WHITE_BISHOP 'B'
#define WHITE_ROOK 'R'
#define WHITE_QUEEN 'Q'
#define WHITE_KING 'K'
#define BLACK_PAWN 'p'
#define BLACK_KNIGHT 'n'
#define BLACK_BISHOP 'b'
#define BLACK_ROOK 'r'
#define BLACK_QUEEN 'q'
#define BLACK_KING 'k'


typedef char** Board;

typedef int bool;
#define true 1;
#define false 0;

Board* InitBoard() {
    char** new_board = (char*)malloc(sizeof(char*) * BOARD_SIDE);
    if (new_board == NULL) { return NULL; }

    for (int i = 0; i < BOARD_SIDE; i++) {
        *(new_board + i) = (char*)malloc(sizeof(char) * BOARD_SIDE);
        if (*(new_board + i) == NULL) { return NULL; }
    }


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
bool LoadFenString(Board* board, const char* fen_string) {
    //rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
}
