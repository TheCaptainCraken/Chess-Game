#include <stdio.h>
#include "../dependencies/include/raylib.h"
#include "libraries/board.h"
#include "libraries/loader.h" 
#include "libraries/events.h"

typedef struct {
    int x, y;
}Move;

Move* GenerateMoves(Move start, Board board, int* nm);
bool CheckMove(Move* moves, int nm, Move move);

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

    char current_player = 'w';
    Move* possible_moves = NULL;
    int number_of_moves = 0;

    bool is_pos_selected = false;
    int selected_row = -1;
    int selected_col = -1;

    /* game loop */
    while (!WindowShouldClose()) {

        if (PlayerClickedOnBoard()) {
            int row, col;
            GetBoardPosition(&row, &col);
            if (!is_pos_selected && *(*(board + row) + col) != EMPTY) {
                if (current_player == 'w' && (*(*(board + row) + col) >= 'A' && *(*(board + row) + col) <= 'Z')) {
                    is_pos_selected = true;
                    selected_col = col;
                    selected_row = row;
                    possible_moves = GenerateMoves((Move) { selected_col, selected_row }, board, & number_of_moves);
                }
                else if (current_player == 'b' && (*(*(board + row) + col) >= 'a' && *(*(board + row) + col) <= 'z')) {
                    is_pos_selected = true;
                    selected_col = col;
                    selected_row = row;
                    possible_moves = GenerateMoves((Move) { selected_col, selected_row }, board, & number_of_moves);
                }
            }
            else if (is_pos_selected && row == selected_row && col == selected_col) {
                is_pos_selected = false;
                selected_row = -1;
                selected_col = -1;
                MemFree(possible_moves);
                number_of_moves = 0;
            }
            else if (is_pos_selected && CheckMove(possible_moves, number_of_moves, (Move) { col, row })) {
                *(*(board + row) + col) = *(*(board + selected_row) + selected_col);
                *(*(board + selected_row) + selected_col) = EMPTY;
                is_pos_selected = false;
                selected_row = -1;
                selected_col = -1;
                MemFree(possible_moves);
                number_of_moves = 0;
                current_player = (current_player == 'w') ? 'b' : 'w';
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

Move* GenerateMoves(Move start, Board board, int* nm) {
    *nm = 1;
    if (*(*(board + start.y) + start.x) >= 'a' && *(*(board + start.y) + start.x) <= 'z') {
        Move* possible_moves = MemAlloc(sizeof(Move));
        *possible_moves = (Move){ start.x, start.y + 1 };
    }
    else {
        Move* possible_moves = MemAlloc(sizeof(Move));
        *possible_moves = (Move){ start.x, start.y - 1 };
    }

}

bool CheckMove(Move* moves, int nm, Move move) {
    for (int i = 0; i < nm; i++) {
        if ((moves + i)->x == move.x && (moves + i)->y == move.y) { return true; }
    }
    return false;
}