#include <stdio.h>
#include "../dependencies/include/raylib.h"
#include "libraries/board.h"
#include "libraries/loader.h" 
#include "libraries/events.h"

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

    bool is_pos_selected = false;
    int selected_row = -1;
    int selected_col = -1;

    /* game loop */
    while (!WindowShouldClose()) {

        if (PlayerClickedOnBoard()) {
            int row, col;
            GetBoardPosition(&row, &col);
            if (!is_pos_selected && *(*(board + row) + col) != EMPTY) {
                is_pos_selected = true;
                selected_col = col;
                selected_row = row;

            }
            else if (is_pos_selected && row == selected_row && col == selected_col) {
                is_pos_selected = false;
                selected_row = -1;
                selected_col = -1;
            }
            else if (is_pos_selected) {
                *(*(board + row) + col) = *(*(board + selected_row) + selected_col);
                *(*(board + selected_row) + selected_col) = EMPTY;
                is_pos_selected = false;
                selected_row = -1;
                selected_col = -1;
            }
        }

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