#pragma once

typedef char** Board;
typedef int bool;

Board* InitBoard();

bool LoadFenString(Board*, const char*);