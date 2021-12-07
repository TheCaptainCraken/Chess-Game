#include "events.h"
#include "board.h"
#include "../../dependencies/include/raylib.h"
#include <stdio.h>

void ProcessEvents(Board board) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

        int step = GetScreenHeight() / BOARD_SIDE; /* step is the lenght of the side of each square */
        int start = (GetScreenWidth() - (step * 8)) / 2; /* start is an offset we calculate to center the board in the window */

        int mouse_x_pos = GetMouseX();
        int mouse_y_pos = GetMouseY();

        if (mouse_x_pos > start && mouse_x_pos < GetScreenWidth() - start) {
            mouse_x_pos -= start;
            int col = (mouse_x_pos / step);
            int row = (mouse_y_pos / step);
            printf("[ %d, %d ]\n", row, col);
            printf("=> %c\n", *(*(board + row) + col));
        }
    }
}

bool PlayerClickedOnBoard() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        int mouse_x_pos = GetMouseX();
        int step = GetScreenHeight() / BOARD_SIDE; /* step is the lenght of the side of each square */
        int start = (GetScreenWidth() - (step * 8)) / 2; /* start is an offset we calculate to center the board in the window */

        return (mouse_x_pos > start && mouse_x_pos < GetScreenWidth() - start);
    }
    else {
        return false;
    }
}

void GetBoardPosition(int* row, int* col) {
    int step = GetScreenHeight() / BOARD_SIDE; /* step is the lenght of the side of each square */
    int start = (GetScreenWidth() - (step * 8)) / 2; /* start is an offset we calculate to center the board in the window */
    int mouse_x_pos = GetMouseX();
    int mouse_y_pos = GetMouseY();
    mouse_x_pos -= start;
    *col = (mouse_x_pos / step);
    *row = (mouse_y_pos / step);
}