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
bool IsWhite(int x, int y, Board board);
bool IsBlack(int x, int y, Board board);
bool IsEmpty(int x, int y, Board board);
char GetPiece(int x, int y, Board board);
bool IsInBoard(int x, int y);

int main(int argc, char** argv) {
    InitWindow(1200, 1000, "Chess"); /* inizalize the window and the OpenGL contex */

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
            if (!is_pos_selected && !IsEmpty(col, row, board)) {
                if (current_player == 'w' && IsWhite(col, row, board)) {
                    is_pos_selected = true;
                    selected_col = col;
                    selected_row = row;
                    possible_moves = GenerateMoves((Move) { selected_col, selected_row }, board, & number_of_moves);
                }
                else if (current_player == 'b' && IsBlack(col, row, board)) {
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
        if (is_pos_selected) {
            int step = GetScreenHeight() / BOARD_SIDE; /* step is the lenght of the side of each square */
            int start = (GetScreenWidth() - (step * 8)) / 2; /* start is an offset we calculate to center the board in the window */
            DrawRectangle((selected_col * step) + start, selected_row * step, step, step, (Color) { 200, 200, 10, 100 });
            for (int i = 0; i < number_of_moves; i++) {
                DrawRectangle(((possible_moves + i)->x * step) + start, (possible_moves + i)->y * step, step, step, (Color) { 200, 10, 10, 100 });
            }
        }
        EndDrawing();
    }

    DestroyBoard(board); /* deallocate the board */
    DestroyAssets(textures); /* deallocate the textures  */
    CloseWindow();
    return 0;
}

Move* GenerateMoves(Move start, Board board, int* nm) {
    *nm = 0;
    Move* possible_moves = NULL;
    if (IsBlack(start.x, start.y, board)) {
        switch (GetPiece(start.x, start.y, board)) {
        case BLACK_PAWN:
        {
            possible_moves = MemAlloc(sizeof(Move) * 4);
            if (start.y == 1 && IsEmpty(start.x, start.y + 2, board) && IsEmpty(start.x, start.y + 1, board)) {
                *(possible_moves + *nm) = (Move){ start.x, start.y + 2 };
                (*nm)++;
            }

            if (IsEmpty(start.x, start.y + 1, board) && IsInBoard(start.x, start.y + 1)) {
                *(possible_moves + *nm) = (Move){ start.x, start.y + 1 };
                (*nm)++;
            }
            if (IsWhite(start.x + 1, start.y + 1, board) && IsInBoard(start.x + 1, start.y + 1)) {
                *(possible_moves + *nm) = (Move){ start.x + 1, start.y + 1 };
                (*nm)++;
            }
            if (IsWhite(start.x - 1, start.y + 1, board) && IsInBoard(start.x - 1, start.y + 1)) {
                *(possible_moves + *nm) = (Move){ start.x - 1, start.y + 1 };
                (*nm)++;
            }
        }
        break;
        case BLACK_ROOK:
        {
            possible_moves = MemAlloc(sizeof(Move) * 16);
            /* go right */
            for (int i = start.x + 1; IsInBoard(i, start.y) && !IsBlack(i, start.y, board); i++) {
                *(possible_moves + *nm) = (Move){ i, start.y };
                (*nm)++;
                if (IsWhite(i, start.y, board)) { break; }
            }
            /* go left */
            for (int i = start.x - 1; IsInBoard(i, start.y) && !IsBlack(i, start.y, board); i--) {
                *(possible_moves + *nm) = (Move){ i, start.y };
                (*nm)++;
                if (IsWhite(i, start.y, board)) { break; }
            }
            /* go down */
            for (int i = start.y + 1; IsInBoard(start.x, i) && !IsBlack(start.x, i, board); i++) {
                *(possible_moves + *nm) = (Move){ start.x, i };
                (*nm)++;
                if (IsWhite(start.x, i, board)) { break; }
            }
            /* go up */
            for (int i = start.y - 1; IsInBoard(start.x, i) && !IsBlack(start.x, i, board); i--) {
                *(possible_moves + *nm) = (Move){ start.x, i };
                (*nm)++;
                if (IsWhite(start.x, i, board)) { break; }
            }
        }
        break;
        case BLACK_BISHOP:
        {
            possible_moves = MemAlloc(sizeof(Move) * 16);
            /* down right */
            for (int i = start.x + 1, j = start.y + 1; IsInBoard(i, j) && !IsBlack(i, j, board); i++, j++) {
                *(possible_moves + *nm) = (Move){ i, j };
                (*nm)++;
                if (IsWhite(i, j, board)) { break; }
            }
            /* down left */
            for (int i = start.x - 1, j = start.y + 1; IsInBoard(i, j) && !IsBlack(i, j, board); i--, j++) {
                *(possible_moves + *nm) = (Move){ i, j };
                (*nm)++;
                if (IsWhite(i, j, board)) { break; }
            }
            /* up right */
            for (int i = start.x + 1, j = start.y - 1; IsInBoard(i, j) && !IsBlack(i, j, board); i++, j--) {
                *(possible_moves + *nm) = (Move){ i, j };
                (*nm)++;
                if (IsWhite(i, j, board)) { break; }
            }
            /* up left */
            for (int i = start.x - 1, j = start.y - 1; IsInBoard(i, j) && !IsBlack(i, j, board); i--, j--) {
                *(possible_moves + *nm) = (Move){ i, j };
                (*nm)++;
                if (IsWhite(i, j, board)) { break; }
            }
        }
        break;
        case BLACK_QUEEN:
        {
            possible_moves = MemAlloc(sizeof(Move) * 32);
            /* down right */
            for (int i = start.x + 1, j = start.y + 1; IsInBoard(i, j) && !IsBlack(i, j, board); i++, j++) {
                *(possible_moves + *nm) = (Move){ i, j };
                (*nm)++;
                if (IsWhite(i, j, board)) { break; }
            }
            /* down left */
            for (int i = start.x - 1, j = start.y + 1; IsInBoard(i, j) && !IsBlack(i, j, board); i--, j++) {
                *(possible_moves + *nm) = (Move){ i, j };
                (*nm)++;
                if (IsWhite(i, j, board)) { break; }
            }
            /* up right */
            for (int i = start.x + 1, j = start.y - 1; IsInBoard(i, j) && !IsBlack(i, j, board); i++, j--) {
                *(possible_moves + *nm) = (Move){ i, j };
                (*nm)++;
                if (IsWhite(i, j, board)) { break; }
            }
            /* up left */
            for (int i = start.x - 1, j = start.y - 1; IsInBoard(i, j) && !IsBlack(i, j, board); i--, j--) {
                *(possible_moves + *nm) = (Move){ i, j };
                (*nm)++;
                if (IsWhite(i, j, board)) { break; }
            }
            /* go right */
            for (int i = start.x + 1; IsInBoard(i, start.y) && !IsBlack(i, start.y, board); i++) {
                *(possible_moves + *nm) = (Move){ i, start.y };
                (*nm)++;
                if (IsWhite(i, start.y, board)) { break; }
            }
            /* go left */
            for (int i = start.x - 1; IsInBoard(i, start.y) && !IsBlack(i, start.y, board); i--) {
                *(possible_moves + *nm) = (Move){ i, start.y };
                (*nm)++;
                if (IsWhite(i, start.y, board)) { break; }
            }
            /* go down */
            for (int i = start.y + 1; IsInBoard(start.x, i) && !IsBlack(start.x, i, board); i++) {
                *(possible_moves + *nm) = (Move){ start.x, i };
                (*nm)++;
                if (IsWhite(start.x, i, board)) { break; }
            }
            /* go up */
            for (int i = start.y - 1; IsInBoard(start.x, i) && !IsBlack(start.x, i, board); i--) {
                *(possible_moves + *nm) = (Move){ start.x, i };
                (*nm)++;
                if (IsWhite(start.x, i, board)) { break; }
            }
        }
        break;
        case BLACK_KING:
        {
            possible_moves = MemAlloc(sizeof(Move) * 8);
            /* all the position anti clockwise sense */
            for (int y = -1; y <= 1; y++) {
                for (int x = -1; x <= 1; x++) {
                    if (!(x == 0 && y == 0)) {
                        if (IsInBoard(start.x + x, start.y + y) && !IsBlack(start.x + x, start.y + y, board)) {
                            *(possible_moves + *nm) = (Move){ start.x + x, start.y + y };
                            (*nm)++;
                        }
                    }
                }
            }

        }
        break;
        default:
        {
            possible_moves = MemAlloc(sizeof(Move));
            *possible_moves = (Move){ start.x, start.y + 1 };
            *nm = 1;
        }
        }
    }
    else {
        switch (GetPiece(start.x, start.y, board)) {
        case WHITE_PAWN:
        {
            possible_moves = MemAlloc(sizeof(Move) * 4);
            if (start.y == 6 && IsEmpty(start.x, start.y - 2, board) && IsEmpty(start.x, start.y - 1, board)) {
                *(possible_moves + *nm) = (Move){ start.x, start.y - 2 };
                (*nm)++;
            }

            if (IsEmpty(start.x, start.y - 1, board) && IsInBoard(start.x, start.y - 1)) {
                *(possible_moves + *nm) = (Move){ start.x, start.y - 1 };
                (*nm)++;
            }
            if (IsBlack(start.x + 1, start.y - 1, board) && IsInBoard(start.x + 1, start.y - 1)) {
                *(possible_moves + *nm) = (Move){ start.x + 1, start.y - 1 };
                (*nm)++;
            }
            if (IsBlack(start.x - 1, start.y - 1, board) && IsInBoard(start.x - 1, start.y - 1)) {
                *(possible_moves + *nm) = (Move){ start.x - 1, start.y - 1 };
                (*nm)++;
            }
        }
        break;
        case WHITE_ROOK:
        {
            possible_moves = MemAlloc(sizeof(Move) * 16);
            /* go right */
            for (int i = start.x + 1; IsInBoard(i, start.y) && !IsWhite(i, start.y, board); i++) {
                *(possible_moves + *nm) = (Move){ i, start.y };
                (*nm)++;
                if (IsBlack(i, start.y, board)) { break; }
            }
            /* go left */
            for (int i = start.x - 1; IsInBoard(i, start.y) && !IsWhite(i, start.y, board); i--) {
                *(possible_moves + *nm) = (Move){ i, start.y };
                (*nm)++;
                if (IsBlack(i, start.y, board)) { break; }
            }
            /* go down */
            for (int i = start.y + 1; IsInBoard(start.x, i) && !IsWhite(start.x, i, board); i++) {
                *(possible_moves + *nm) = (Move){ start.x, i };
                (*nm)++;
                if (IsBlack(start.x, i, board)) { break; }
            }
            /* go up */
            for (int i = start.y - 1; IsInBoard(start.x, i) && !IsWhite(start.x, i, board); i--) {
                *(possible_moves + *nm) = (Move){ start.x, i };
                (*nm)++;
                if (IsBlack(start.x, i, board)) { break; }
            }
        }
        break;
        case WHITE_BISHOP:
        {
            possible_moves = MemAlloc(sizeof(Move) * 16);
            /* down right */
            for (int i = start.x + 1, j = start.y + 1; IsInBoard(i, j) && !IsWhite(i, j, board); i++, j++) {
                *(possible_moves + *nm) = (Move){ i, j };
                (*nm)++;
                if (IsBlack(i, j, board)) { break; }
            }
            /* down left */
            for (int i = start.x - 1, j = start.y + 1; IsInBoard(i, j) && !IsWhite(i, j, board); i--, j++) {
                *(possible_moves + *nm) = (Move){ i, j };
                (*nm)++;
                if (IsBlack(i, j, board)) { break; }
            }
            /* up right */
            for (int i = start.x + 1, j = start.y - 1; IsInBoard(i, j) && !IsWhite(i, j, board); i++, j--) {
                *(possible_moves + *nm) = (Move){ i, j };
                (*nm)++;
                if (IsBlack(i, j, board)) { break; }
            }
            /* up left */
            for (int i = start.x - 1, j = start.y - 1; IsInBoard(i, j) && !IsWhite(i, j, board); i--, j--) {
                *(possible_moves + *nm) = (Move){ i, j };
                (*nm)++;
                if (IsBlack(i, j, board)) { break; }
            }
        }
        break;
        case WHITE_QUEEN:
        {
            possible_moves = MemAlloc(sizeof(Move) * 32);
            /* down right */
            for (int i = start.x + 1, j = start.y + 1; IsInBoard(i, j) && !IsWhite(i, j, board); i++, j++) {
                *(possible_moves + *nm) = (Move){ i, j };
                (*nm)++;
                if (IsBlack(i, j, board)) { break; }
            }
            /* down left */
            for (int i = start.x - 1, j = start.y + 1; IsInBoard(i, j) && !IsWhite(i, j, board); i--, j++) {
                *(possible_moves + *nm) = (Move){ i, j };
                (*nm)++;
                if (IsBlack(i, j, board)) { break; }
            }
            /* up right */
            for (int i = start.x + 1, j = start.y - 1; IsInBoard(i, j) && !IsWhite(i, j, board); i++, j--) {
                *(possible_moves + *nm) = (Move){ i, j };
                (*nm)++;
                if (IsBlack(i, j, board)) { break; }
            }
            /* up left */
            for (int i = start.x - 1, j = start.y - 1; IsInBoard(i, j) && !IsWhite(i, j, board); i--, j--) {
                *(possible_moves + *nm) = (Move){ i, j };
                (*nm)++;
                if (IsBlack(i, j, board)) { break; }
            }
            /* go right */
            for (int i = start.x + 1; IsInBoard(i, start.y) && !IsWhite(i, start.y, board); i++) {
                *(possible_moves + *nm) = (Move){ i, start.y };
                (*nm)++;
                if (IsBlack(i, start.y, board)) { break; }
            }
            /* go left */
            for (int i = start.x - 1; IsInBoard(i, start.y) && !IsWhite(i, start.y, board); i--) {
                *(possible_moves + *nm) = (Move){ i, start.y };
                (*nm)++;
                if (IsBlack(i, start.y, board)) { break; }
            }
            /* go down */
            for (int i = start.y + 1; IsInBoard(start.x, i) && !IsWhite(start.x, i, board); i++) {
                *(possible_moves + *nm) = (Move){ start.x, i };
                (*nm)++;
                if (IsBlack(start.x, i, board)) { break; }
            }
            /* go up */
            for (int i = start.y - 1; IsInBoard(start.x, i) && !IsWhite(start.x, i, board); i--) {
                *(possible_moves + *nm) = (Move){ start.x, i };
                (*nm)++;
                if (IsBlack(start.x, i, board)) { break; }
            }
        }
        break;
        case WHITE_KING:
        {
            possible_moves = MemAlloc(sizeof(Move) * 8);
            /* all the position anti clockwise sense */
            for (int y = -1; y <= 1; y++) {
                for (int x = -1; x <= 1; x++) {
                    if (!(x == 0 && y == 0)) {
                        if (IsInBoard(start.x + x, start.y + y) && !IsWhite(start.x + x, start.y + y, board)) {
                            *(possible_moves + *nm) = (Move){ start.x + x, start.y + y };
                            (*nm)++;
                        }
                    }
                }
            }

        }
        break;
        default:
        {
            possible_moves = MemAlloc(sizeof(Move));
            *possible_moves = (Move){ start.x, start.y - 1 };
            *nm = 1;
        }
        }
    }
    return possible_moves;
}

bool CheckMove(Move* moves, int nm, Move move) {
    for (int i = 0; i < nm; i++) {
        if ((moves + i)->x == move.x && (moves + i)->y == move.y) { return true; }
    }
    return false;
}

bool IsWhite(int x, int y, Board board) {
    if (GetPiece(x, y, board) >= 'A' && GetPiece(x, y, board) <= 'Z' && GetPiece(x, y, board) != EMPTY) {
        return true;
    }
    return false;
}

bool IsBlack(int x, int y, Board board) {
    if (GetPiece(x, y, board) >= 'a' && GetPiece(x, y, board) <= 'z' && GetPiece(x, y, board) != EMPTY) {
        return true;
    }
    return false;
}

bool IsEmpty(int x, int y, Board board) {
    return (GetPiece(x, y, board) == EMPTY);
}

char GetPiece(int x, int y, Board board) {
    return *(*(board + y) + x);
}

bool IsInBoard(int x, int y) {
    return (x < 8 && x > -1 && y > -1 && y < 8);
}