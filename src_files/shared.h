#ifndef SHARED_H
#define SHARED_H

#define SQUARE_WIDTH 70
#define SQUARE_HEIGHT 70

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8
#define AMOUNT_OF_CHESS_SQUARES BOARD_WIDTH * BOARD_HEIGHT
#define FONT_SIZE 45
#define TITLE_SIZE 100


typedef enum {
    W_KING,
    W_QUEEN,
    W_PAWN,
    W_BISHOP,
    W_KNIGHT,
    W_ROOK,
    B_KING,
    B_QUEEN,
    B_PAWN,
    B_BISHOP,
    B_KNIGHT,
    B_ROOK,
    NONE
} chess_piece;

typedef struct {
    int width;
    int height; 
    int row; 
    int col; 
    chess_piece piece;
} chess_square;


#endif
