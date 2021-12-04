#pragma once

typedef char** Board;

#if !defined (true) && !defined (false)
typedef int bool;
#define true 1;
#define false 0;
#endif

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

Board InitBoard();

bool LoadFenString(Board, const char*);
void PrintBoardOnTerminal(Board);