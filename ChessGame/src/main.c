#include "../dependencies/include/raylib.h"
#include <stdio.h>
#include "libraries/board.h"
#include "libraries/loader.h" 

int main(void) {
    InitWindow(1000, 800, "Chess");
    Board board = InitBoard();
    int step = GetScreenHeight() / BOARD_SIDE;
    Texture2D* textures = LoadAssets(step);
    if (board == NULL || textures == NULL) {/*the board initalization failed */
        CloseWindow();
        return 1;
    }
    LoadFenString(board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"); /* this is the initial state */
    PrintBoardOnTerminal(board);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(PURPLE);
        PrintBoard(board, textures);
        EndDrawing();
    }
    DestroyBoard(board); /* deallocate the board */
    DestroyAssets(textures); /* deallocate the textures  */
    CloseWindow();

    return 0;
}