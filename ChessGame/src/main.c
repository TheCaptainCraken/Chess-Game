#include "../dependencies/include/raylib.h"
#include <stdio.h>
#include "libraries/board.h"
#include "libraries/loader.h"

int main(void) {
    InitWindow(1000, 800, "Chess");
    Board board = InitBoard();
    const int step = BOARD_SIDE / GetScreenHeight();
    Texture2D* textures = LoadAssets(step);
    if (board == NULL || textures == NULL) {/*the board initalization failed */
        CloseWindow();
        return 1;
    }
    LoadFenString(board, "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"); /* this is the initial state */
    PrintBoardOnTerminal(board);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        PrintBoard(board, textures);
        EndDrawing();
    }
    DestroyBoard(board); /* deallocate the board */
    DestroyAssets(textures); /* deallocate the textures */
    CloseWindow();

    return 0;
}