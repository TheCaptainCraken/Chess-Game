#pragma once

typedef char** Board;

Board* InitBoard();

bool LoadFenString(Board*, const char*);