#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shared.h"
#include <ctype.h>


Texture2D piece_to_pic(chess_piece piece, Texture2D wP, Texture2D wK, Texture2D wQ, Texture2D wB, Texture2D wN, Texture2D wR, Texture2D bK, Texture2D bQ, Texture2D bB, Texture2D bN, Texture2D bR, Texture2D bP, Texture2D blank) {
    Texture2D piece_pic;
    switch (piece) {
        case W_PAWN: 
            piece_pic = wP;
            break;
        case W_KING: 
            piece_pic = wK;
            break;
        case W_QUEEN: 
            piece_pic = wQ;
            break;
        case W_BISHOP: 
            piece_pic = wB;
            break;
        case W_KNIGHT: 
            piece_pic = wN;
            break;
        case W_ROOK: 
            piece_pic = wR;
            break;
        case B_PAWN: 
            piece_pic = bP;
            break;
        case B_KING: 
            piece_pic = bK;
            break;
        case B_QUEEN: 
            piece_pic = bQ;
            break;
        case B_BISHOP: 
            piece_pic = bB;
            break;
        case B_KNIGHT: 
            piece_pic = bN;
            break;
        case B_ROOK: 
            piece_pic = bR;
            break;
        default:
            piece_pic = blank;
            break;

    }
    piece_pic.height = SQUARE_HEIGHT - 2;
    piece_pic.width = SQUARE_WIDTH - 2;
    return piece_pic;
}

void ClearBoard(chess_square chess_board[BOARD_HEIGHT][BOARD_WIDTH]) {
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            chess_board[x][y].piece = NONE;
        }
    }
}

void ResetBoard(chess_square chess_board[BOARD_HEIGHT][BOARD_WIDTH]) {

    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            chess_board[x][y].piece = NONE;
        }
    }

    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            if (y == 6) {
                chess_board[x][y].piece = W_PAWN;
            }
            if (y == 1) {
                chess_board[x][y].piece = B_PAWN;
            }
            if ( y == 0 ) {
                if (x == 0 || x == 7) {
                    chess_board[x][y].piece = B_ROOK;
                }
                if (x == 1 || x == 6) {
                    chess_board[x][y].piece = B_KNIGHT;
                }
                if (x == 2 || x == 5) {
                    chess_board[x][y].piece = B_BISHOP;
                }
                if (x == 3 ) {
                    chess_board[x][y].piece = B_QUEEN;
                }
                if (x == 4 ) {
                    chess_board[x][y].piece = B_KING;
                }
            }
            if ( y == 7 ) {
                if (x == 0 || x == 7) {
                    chess_board[x][y].piece = W_ROOK;
                }
                if (x == 1 || x == 6) {
                    chess_board[x][y].piece = W_KNIGHT;
                }
                if (x == 2 || x == 5) {
                    chess_board[x][y].piece = W_BISHOP;
                }
                if (x == 3 ) {
                    chess_board[x][y].piece = W_QUEEN;
                }
                if (x == 4 ) {
                    chess_board[x][y].piece = W_KING;
                }
            }
        }
    }
}



void DrawPlacement(chess_square chess_board[8][8],int squareState[8][8],chess_piece *hand_buffer,int board_origin_x, int board_origin_y, Texture2D wP, Texture2D wK, Texture2D wQ, Texture2D wB, Texture2D wN, Texture2D wR, Texture2D bK, Texture2D bQ, Texture2D bB, Texture2D bN, Texture2D bR, Texture2D bP,Texture2D blank) {
        for (int y = 0; y < BOARD_HEIGHT; y++)
        {
            for (int x = 0; x < BOARD_WIDTH; x++)
            {
                chess_square cur_sqr = chess_board[x][y];
                if (squareState[x][y])
                {
                    if (cur_sqr.piece != NONE && *hand_buffer == NONE) {
                        *hand_buffer = chess_board[x][y].piece;
                        chess_board[x][y].piece = NONE;
                    }
                    else if (cur_sqr.piece != NONE && *hand_buffer != NONE) {
                        chess_board[x][y].piece = *hand_buffer;
                        *hand_buffer = NONE;
                    }
                    else if (cur_sqr.piece == NONE && *hand_buffer != NONE) {
                        chess_board[x][y].piece = *hand_buffer;
                        *hand_buffer = NONE;
                    }
                    else {
                        Texture2D piece_texture =  piece_to_pic(cur_sqr.piece,  wP,  wK,  wQ,  wB,  wN,  wR,  bK,  bQ,  bB,  bN,  bR,  bP,blank);
                        DrawTexture(piece_texture,board_origin_x + SQUARE_WIDTH*x, board_origin_y + SQUARE_WIDTH*y , WHITE);
                        *hand_buffer = NONE;
                    }

                }
            }
        }
}

void DrawBoard(int board_origin_x, int board_origin_y,chess_square chess_board[BOARD_HEIGHT][BOARD_WIDTH], int show_names,char* numbers[8], char* letters[8],Texture2D wP, Texture2D wK, Texture2D wQ, Texture2D wB, Texture2D wN, Texture2D wR, Texture2D bK, Texture2D bQ, Texture2D bB, Texture2D bN, Texture2D bR, Texture2D bP,Texture2D blank) {
        for (int y = 0; y < BOARD_HEIGHT; y++)
        {
            DrawText(numbers[y],board_origin_x + BOARD_WIDTH - SQUARE_WIDTH + 15,board_origin_y + SQUARE_HEIGHT*y + (SQUARE_HEIGHT / 3) - 10,FONT_SIZE, GRAY);
            for (int x = 0; x < BOARD_WIDTH; x++)
            {
                DrawText(letters[x],board_origin_x + SQUARE_WIDTH*x + (SQUARE_WIDTH / 3), board_origin_y + SQUARE_HEIGHT*BOARD_HEIGHT, FONT_SIZE, GRAY);

                chess_square cur_sqr = chess_board[x][y];
                DrawRectangle(board_origin_x + SQUARE_WIDTH*x, board_origin_y + SQUARE_HEIGHT*y, cur_sqr.width, cur_sqr.height, ( (cur_sqr.row % 2) == (cur_sqr.col %2) ) ? WHITE : BEIGE);
                if (cur_sqr.piece != NONE)   {
                    Texture2D piece_texture =  piece_to_pic(cur_sqr.piece,  wP,  wK,  wQ,  wB,  wN,  wR,  bK,  bQ,  bB,  bN,  bR,  bP,blank);
                    DrawTexture(piece_texture,board_origin_x + SQUARE_WIDTH*x, board_origin_y + SQUARE_WIDTH*y , WHITE);
                }

                if (show_names)
                {
                    DrawRectangle(board_origin_x + SQUARE_WIDTH*x, board_origin_y + SQUARE_HEIGHT*y, cur_sqr.width, cur_sqr.height, ( (cur_sqr.row % 2) == (cur_sqr.col %2) ) ? WHITE : BEIGE);

                    char square_name[30];
                    sprintf(square_name,"%s%s",letters[x],numbers[y]);
                    DrawText(square_name,board_origin_x + SQUARE_WIDTH*x + (SQUARE_WIDTH/4) , board_origin_y + SQUARE_HEIGHT*y + (SQUARE_HEIGHT/4),SQUARE_WIDTH/2,GRAY);
                }
            }
        }
}


void ReverseStrArray(char* arr[], int n)
{
    char* temp;
  
    // Move from begin and end. Keep
    // swapping strings. 
    int j = n - 1;
    for (int i = 0; i < j; i++) {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        j--;
    }
}

void ReverseBoardArray(chess_square arr[], int n)
{
    chess_square temp;
  
    // Move from begin and end. Keep
    // swapping strings. 
    int j = n - 1;
    for (int i = 0; i < j; i++) {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        j--;
    }
}


chess_piece fen_to_enum(char fen_name) {
    chess_piece cp;
    switch(fen_name)
    {
    case 'P':
        cp = W_PAWN;
        break;
    case 'R':
        cp = W_ROOK;
        break;
    case 'Q':
        cp = W_QUEEN;
        break;
    case 'B':
        cp = W_BISHOP;
        break;
    case 'N':
        cp = W_KNIGHT;
        break;
    case 'K':
        cp = W_KING;
        break;
    case 'p':
        cp = B_PAWN;
        break;
    case 'r':
        cp = B_ROOK;
        break;
    case 'q':
        cp = B_QUEEN;
        break;
    case 'b':
        cp = B_BISHOP;
        break;
    case 'n':
        cp = B_KNIGHT;
        break;
    case 'k':
        cp = B_KING;
        break;

    default: 
        cp = NONE;
    }
    return cp;
}

char enum_to_fen(chess_piece piece) {
    char cp;
    switch(piece)
    {
    case W_PAWN:
        cp = 'P';
        break;
    case W_ROOK:
        cp = 'R';
        break;
    case W_QUEEN:
        cp = 'Q';
        break;
    case W_BISHOP:
        cp = 'B';
        break;
    case W_KNIGHT:
        cp = 'N';
        break;
    case W_KING:
        cp = 'K';
        break;
    case B_PAWN:
        cp = 'p';
        break;
    case B_ROOK:
        cp = 'r';
        break;
    case B_QUEEN:
        cp = 'q';
        break;
    case B_BISHOP:
        cp = 'b';
        break;
    case B_KNIGHT:
        cp = 'n';
        break;
    case B_KING:
        cp = 'k';
        break;
    case NONE:
        cp = 'O';
        break;

    default: 
        cp = '\0';
    }
    return cp;
}

void board_to_fen(chess_square chess_board[8][8], char fen_string[100],int flip,int history_len) {
    /* 
       Fen string format is like: rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 
       */
    
    history_len--;

    if (flip) {
        /* unflip */
        chess_square tmp[8][8];
        for(int i = 0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                tmp[i][j] = chess_board[8-i-1][8-j-1];
            }
        }

        memcpy(chess_board,tmp,sizeof(tmp));
    }

    int blank_count = 0;
    int string_index = 0;
    char tmp[50];
    for (int i = 0; i<8; i++) {
        for (int j = 0; j<8; j++) {
            chess_piece current_piece = chess_board[j][i].piece;  
            if (current_piece == NONE) {
                blank_count++;
            }
            else {
                if (blank_count > 0) {
                    tmp[string_index] = blank_count + '0';
                    string_index++;
                    blank_count = 0;
                }
                char piece_char = enum_to_fen(current_piece);
                tmp[string_index] = piece_char;
                string_index++;
            }
        }
        if (blank_count > 0) {
            tmp[string_index] = blank_count + '0';
            string_index++;
            blank_count = 0;
        }
        if (i != 7) {
        tmp[string_index] = '/';
        string_index++;
        }
        else {
            tmp[string_index] = '\0';
        }
    };
    char active_colour = flip ? 'b' : 'w';
    char enpass = '-'; /* Do not check if en passent is possible */

    /* check castling */
    char castling_rights[5] = "";
    int castling_index = 0;

    //DEBUG

    if (chess_board[4][7].piece == W_KING && chess_board[7][7].piece == W_ROOK) {
        castling_rights[castling_index++] = 'K';
    }
    if (chess_board[4][7].piece == W_KING && chess_board[0][7].piece == W_ROOK) {
        castling_rights[castling_index++] = 'Q';
    }
    if (chess_board[4][0].piece == B_KING && chess_board[7][0].piece == B_ROOK) {
        castling_rights[castling_index++] = 'k';
    }
    if (chess_board[4][0].piece == B_KING && chess_board[0][0].piece == B_ROOK) {
        castling_rights[castling_index++] = 'q';
    }

    sprintf(fen_string,"%s - %c %c %s %d %d",tmp,active_colour,enpass,castling_rights,0,history_len);
}

void parse_fen(chess_square chess_board[8][8],char* fen_string){
    /* 
    Fen string format is like: rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 
    For matching the board, we do not care about anything after the first space
    */
    char *row;
    char row_proper[8 * sizeof(char)];
    int x = 0;
    int y = 0;
    row = strtok(fen_string,"/");
    /* get the first token */
    /* walk through other tokens */
    while( row != NULL ) {
        strncpy(row_proper,row,8*sizeof(char));
        
        char c;
         for (int i = 0; i < (int)strlen(row_proper); i++) {
             c = row_proper[i];
             if (isdigit(c)) {
                int d = c - '0';
                for (int j = 0; j < d; j++) {
                    chess_board[x + j][y].piece = NONE;
                }
                x+=d;
             }
             else {
                chess_board[x][y].piece = fen_to_enum(c);
                x++;
             }
             
         }
        row = strtok(NULL, "/");
        x = 0;
        y++;

    }
}


void ListenForKeys(chess_square chess_board[8][8], chess_square chess_board_history[100][8][8], int history_len,int* history_index ,chess_piece *hand_buffer, int *flip, int flipped) {
    if (IsKeyPressed(KEY_Q))
    {
        *hand_buffer = W_QUEEN;
    }
    if (IsKeyPressed(KEY_K))
    {
        *hand_buffer = W_KING;
    }
    if (IsKeyPressed(KEY_P))
    {
        *hand_buffer = W_PAWN;
    }
    if (IsKeyPressed(KEY_N))
    {
        *hand_buffer = W_KNIGHT;
    }
    if (IsKeyPressed(KEY_R))
    {
        *hand_buffer = W_ROOK;
    }
    if (IsKeyPressed(KEY_B))
    {
        *hand_buffer = W_BISHOP;
    }
    if (IsKeyPressed(KEY_Q) && IsKeyDown(KEY_LEFT_SHIFT))
    {
        *hand_buffer = B_QUEEN;
    }
    if (IsKeyPressed(KEY_K) && IsKeyDown(KEY_LEFT_SHIFT))
    {
        *hand_buffer = B_KING;
    }
    if (IsKeyPressed(KEY_P) && IsKeyDown(KEY_LEFT_SHIFT))
    {
        *hand_buffer = B_PAWN;
    }
    if (IsKeyPressed(KEY_N) && IsKeyDown(KEY_LEFT_SHIFT))
    {
        *hand_buffer = B_KNIGHT;
    }
    if (IsKeyPressed(KEY_R) && IsKeyDown(KEY_LEFT_SHIFT))
    {
        *hand_buffer = B_ROOK;
    }
    if (IsKeyPressed(KEY_B) && IsKeyDown(KEY_LEFT_SHIFT))
    {
        *hand_buffer = B_BISHOP;
    }
    if (IsKeyPressed(KEY_C) && IsKeyDown(KEY_LEFT_SHIFT))
    {
        ClearBoard(chess_board);
    }
    if (IsKeyPressed(KEY_L))
    {
        *history_index = *history_index + 1;
        if (*history_index > history_len) {
            *history_index = history_len;
        }
        memcpy(chess_board,chess_board_history[*history_index],sizeof(chess_board_history[*history_index]));
    }
    if (IsKeyPressed(KEY_H))
    {
        *history_index = *history_index-1;
        if (*history_index < 0) {
            *history_index = 0;
        }
        memcpy(chess_board,chess_board_history[*history_index],sizeof(chess_board_history[*history_index]));
    }

    if (IsKeyPressed(KEY_C) && !IsKeyDown(KEY_LEFT_SHIFT))
    {
        ResetBoard(chess_board);
    }

    if (IsKeyPressed(KEY_D))
    {
        char* home = getenv("HOME");
        char path_to_fen[100];
        sprintf(path_to_fen,"%s/.local/share/chess/fen.txt",home);

        char fen_string[100];
        chess_square chess_board_cpy[8][8];
        memcpy(chess_board_cpy,chess_board,sizeof(chess_board_cpy));
        board_to_fen(chess_board_cpy,fen_string,flipped,history_len);
        
        FILE *f = fopen(path_to_fen,"a");
        if (f == NULL) {
            fprintf(stderr,"Unable to open fen path\n");
        }
        fprintf(f,fen_string);
        fprintf(f,"\n");
        fclose(f);
    }
    if (IsKeyPressed(KEY_F))
    {
        *flip = *flip - 1;
    }

}
