#include "../dependencies/include/raylib.h"
#include <stdio.h>
#include "libraries/board.h"

int main(void) {
    InitWindow(800, 450, "Chess");
    Print();
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}