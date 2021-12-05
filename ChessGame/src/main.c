#include <stdio.h>
#include "../dependencies/include/raylib.h"
#include "libraries/board.h"
#include "libraries/loader.h" 

int main(int argc, char** argv) {
    InitWindow(1000, 800, "Chess"); /* inizalize the window and the OpenGL contex */

    Board board = InitBoard(); /* create a an empty game board in memory */

    int step = GetScreenHeight() / BOARD_SIDE; /* create and resize the textures and load them in vram */
    Texture2D* textures = LoadAssets(step);

    if (board == NULL || textures == NULL) { /*the board initalization or the texture loading failed */
        if (board) DestroyBoard(board);
        if (textures) DestroyAssets(textures);
        CloseWindow();
        return 1;
    }

    LoadFenString(board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"); /* this is the initial state */
    PrintBoardOnTerminal(board); /* for debug porpuses */

    /* game loop */
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(PURPLE);
        PrintBoard(board, textures); /* displays the board on a GUI */
        EndDrawing();
    }

    DestroyBoard(board); /* deallocate the board */
    DestroyAssets(textures); /* deallocate the textures  */
    CloseWindow();
    return 0;
}