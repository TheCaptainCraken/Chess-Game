#include "../dependencies/include/raylib.h"
#include <stdio.h>
#include "libraries/board.h"

int main(void) {
    InitWindow(800, 450, "Chess");
    Board board = InitBoard();
    if (board == NULL) {/*the board initalization failed */
        CloseWindow();
        return 1;
    }
    LoadFenString(board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    PrintBoardOnTerminal(board);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}