#include "../dependencies/include/raylib.h"
#include <stdio.h>
#include "libraries/board.h"

int main(void) {
    InitWindow(800, 450, "Chess");
    // Board* board = InitBoard();
    // if (board == NULL) {/*the board initalization failed */
    //     CloseWindow();
    //     return 1;
    // }
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}