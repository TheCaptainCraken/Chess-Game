#pragma once
#include "../../dependencies/include/raylib.h"

#define IMG_SIDE_LEN 20

#define BLACK_BISHOP_IMAGE_PATH "assets/black_bishop.png"
#define BLACK_KING_IMAGE_PATH "assets/black_king.png"
#define BLACK_KNIGHT_IMAGE_PATH "assets/black_knight.png"
#define BLACK_PAWN_IMAGE_PATH "assets/black_pawn.png"
#define BLACK_QUEEN_IMAGE_PATH "assets/black_queen.png"
#define BLACK_ROOK_IMAGE_PATH "assets/black_rook.png"
#define WHITE_BISHOP_IMAGE_PATH "assets/white_bishop.png"
#define WHITE_KING_IMAGE_PATH "assets/white_king.png"
#define WHITE_KNIGHT_IMAGE_PATH "assets/white_knight.png"
#define WHITE_PAWN_IMAGE_PATH "assets/white_pawn.png"
#define WHITE_QUEEN_IMAGE_PATH "assets/white_queen.png"
#define WHITE_ROOK_IMAGE_PATH "assets/white_rook.png"

Texture2D* LoadAssets(int);
void DestroyAssets(Texture2D*);