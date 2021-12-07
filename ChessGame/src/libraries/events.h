#pragma once
#include "../../dependencies/include/raylib.h"
#include "board.h"

void ProcessEvents(Board board);
bool PlayerClickedOnBoard();
void GetBoardPosition(int* row, int* col);