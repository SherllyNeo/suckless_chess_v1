#ifndef CHESS_H
#define CHESS_H
#include "chess.c"
#include "shared.h"

void DrawBoard(int board_origin_x, int board_origin_y, chess_square chess_board[BOARD_HEIGHT][BOARD_WIDTH], int show_names, char *numbers[8], char *letters[8], Texture2D wP, Texture2D wK, Texture2D wQ, Texture2D wB, Texture2D wN, Texture2D wR, Texture2D bK, Texture2D bQ, Texture2D bB, Texture2D bN, Texture2D bR, Texture2D bP, Texture2D blank);
void DrawPlacement(chess_square chess_board[BOARD_HEIGHT][BOARD_WIDTH],int square_state[BOARD_HEIGHT][BOARD_WIDTH],chess_piece *hand_buffer, int board_origin_x, int board_origin_y, Texture2D wP, Texture2D wK, Texture2D wQ, Texture2D wB, Texture2D wN, Texture2D wR, Texture2D bK, Texture2D bQ, Texture2D bB, Texture2D bN, Texture2D bR, Texture2D bP, Texture2D blank);


void ListenForKeys(chess_square chess_board[BOARD_HEIGHT][BOARD_WIDTH], chess_square chess_board_history[100][BOARD_HEIGHT][BOARD_WIDTH], int * history_len,int * history_index ,chess_piece *hand_buffer, int *flip,int flipped);

void ReverseStrArray(char **arr, int n);
void ReverseBoardArray(chess_square *arr, int n);
void ResetBoard(chess_square chess_board[BOARD_HEIGHT][BOARD_WIDTH]);
void ClearBoard(chess_square chess_board[BOARD_HEIGHT][BOARD_WIDTH]);




#endif


