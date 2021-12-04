#pragma once

typedef char** Board;

/*
*   Definition of bool type {0 is false, 1 is true}
*/
#if !defined (true) && !defined (false)
typedef int bool;
#define true 1;
#define false 0;
#endif

/*
*   Definitions for the board, we use FEN notation (https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation)
*   to define every piece on the board and an empty space to indicate that no piece is in that position
*/
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

/* allocates in memory the space for a new board and returns it */
Board InitBoard();

/* loads into the board the positions from a FEN string */
bool LoadFenString(Board, const char*);
/* prints the current state of a board on the terminal */
void PrintBoardOnTerminal(Board);
/* prints the current state of a board on the GUI*/
void PrintBoard(Board, Texture2D*);

/* deallocates the board */
void DestroyBoard(Board);