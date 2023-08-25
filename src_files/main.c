#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SQUARE_WIDTH 60
#define SQUARE_HEIGHT 60

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

void ListenForKeys(chess_square chess_board[8][8], chess_piece *hand_buffer, int *flip) {
    if (IsKeyPressed(KEY_Q))
    {
        *hand_buffer = W_QUEEN;
    }
    if (IsKeyPressed(KEY_F))
    {
        *flip = *flip - 1;
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

    if (IsKeyPressed(KEY_C) && !IsKeyDown(KEY_LEFT_SHIFT))
    {
        ResetBoard(chess_board);
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
void ReverseBoard(chess_square chess_board[BOARD_HEIGHT][BOARD_WIDTH],char* letters[8], char* numbers[8]) {
    ReverseStrArray(letters,8);
    ReverseStrArray(numbers,8);
    chess_square tmp[BOARD_HEIGHT][BOARD_WIDTH];
//     for (int y = 0; y < BOARD_HEIGHT; y++)
//     {
//         for (int x = 0; x < BOARD_WIDTH; x++)
//         {
//             tmp[x][y] = chess_board[BOARD_WIDTH - x - 1][BOARD_HEIGHT - y - 1];
//         }
//     }
//    memset(chess_board,0,AMOUNT_OF_CHESS_SQUARES*sizeof(chess_square));

}

int main(void)
{
    const int screenWidth = 900;
    const int screenHeight = 900;
    chess_square chess_board[BOARD_WIDTH][BOARD_HEIGHT];
    float board_origin_x = screenWidth / 20;
    float board_origin_y = screenHeight / 5;


    /* INIT BOARD */

    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            chess_board[x][y].width = SQUARE_WIDTH;
            chess_board[x][y].height = SQUARE_HEIGHT;
            chess_board[x][y].row = y;
            chess_board[x][y].col = x;
            chess_board[x][y].piece = NONE;
        }
    }
    ResetBoard(chess_board);


    /* Make window resizable */
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);  
    InitWindow(screenWidth, screenHeight, "Simple Chess");

    char* home = getenv("HOME");
    char path_to_assets[100];
    sprintf(path_to_assets,"%s/.local/share/chess/chess_pieces/",home);

    char path_to_wp[200];
    char path_to_wk[200];
    char path_to_wq[200];
    char path_to_wb[200];
    char path_to_wn[200];
    char path_to_wr[200];
    char path_to_bk[200];
    char path_to_bq[200];
    char path_to_bb[200];
    char path_to_bn[200];
    char path_to_br[200];
    char path_to_bp[200];
    char path_to_blank[200];

    sprintf(path_to_wp,"%s%s",path_to_assets,"wP.png");
    sprintf(path_to_wk,"%s%s",path_to_assets,"wK.png");
    sprintf(path_to_wq,"%s%s",path_to_assets,"wQ.png");
    sprintf(path_to_wb,"%s%s",path_to_assets,"wB.png");
    sprintf(path_to_wn,"%s%s",path_to_assets,"wN.png");
    sprintf(path_to_wr,"%s%s",path_to_assets,"wR.png");
    sprintf(path_to_bk,"%s%s",path_to_assets,"bK.png");
    sprintf(path_to_bq,"%s%s",path_to_assets,"bQ.png");
    sprintf(path_to_bb,"%s%s",path_to_assets,"bB.png");
    sprintf(path_to_bn,"%s%s",path_to_assets,"bN.png");
    sprintf(path_to_br,"%s%s",path_to_assets,"bR.png");
    sprintf(path_to_bp,"%s%s",path_to_assets,"bP.png");
    sprintf(path_to_blank,"%s%s",path_to_assets,"blank.png");

    printf("\npath to white pawn: %s\n",path_to_bp);

    Texture2D wP = LoadTexture(path_to_wp);
    Texture2D wK = LoadTexture(path_to_wk);
    Texture2D wQ = LoadTexture(path_to_wq);
    Texture2D wB = LoadTexture(path_to_wb);
    Texture2D wN = LoadTexture(path_to_wn);
    Texture2D wR = LoadTexture(path_to_wr);
    Texture2D bK = LoadTexture(path_to_bk);
    Texture2D bQ = LoadTexture(path_to_bq);
    Texture2D bB = LoadTexture(path_to_bb);
    Texture2D bN = LoadTexture(path_to_bn);
    Texture2D bR = LoadTexture(path_to_br);
    Texture2D bP = LoadTexture(path_to_bp);
    Texture2D blank = LoadTexture(path_to_blank);


    char* letters[8] = {"A","B","C","D","E","F","G","H"};
    char* numbers[8] = {"8","7","6","5","4","3","2","1"};
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    Vector2 mousePoint = { 0.0f, 0.0f };
    chess_piece hand_buffer = NONE;
    int squareState[BOARD_WIDTH][BOARD_HEIGHT] = { 0 };
    int show_names = 0;
    int flip = 0;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        /* Check for mouse position and interaction with board */
        mousePoint = GetMousePosition();
        for (int y = 0; y < BOARD_HEIGHT; y++)
        {
            for (int x = 0; x < BOARD_WIDTH; x++)
            {
                chess_square cur_sqr = chess_board[x][y];
                Rectangle chess_square_as_rec;
                chess_square_as_rec.x = board_origin_x + SQUARE_WIDTH*x;
                chess_square_as_rec.y = board_origin_y + SQUARE_HEIGHT*y;
                chess_square_as_rec.width = cur_sqr.width;
                chess_square_as_rec.height = cur_sqr.height;
                if (CheckCollisionPointRec(mousePoint,chess_square_as_rec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    squareState[x][y] = 1;
                }
                else if (CheckCollisionPointRec(mousePoint,chess_square_as_rec) && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                    chess_board[x][y].piece = NONE;
                }
                else  {
                    squareState[x][y] = 0;
                }
            }
        }

        /* draw board */
        if (flip) {
            ReverseStrArray(letters, BOARD_WIDTH);
            ReverseStrArray(numbers, BOARD_HEIGHT);
            for (int i = 0; i<BOARD_HEIGHT; i++) {
                ReverseBoardArray(chess_board[i],BOARD_WIDTH);
            }
            flip = 0;
        }
        DrawBoard(board_origin_x,board_origin_y,chess_board,show_names,numbers,letters,wP,  wK,  wQ,  wB,  wN,  wR,  bK,  bQ,  bB,  bN,  bR,  bP,  blank);

        /* toggle show names flag */
        if (IsKeyPressed(KEY_SPACE)) 
            show_names = !show_names;

        /* DRAW */
        BeginDrawing();
        DrawText("Simple Chess",0, 0, TITLE_SIZE, BLACK);

        ClearBackground(BROWN);


        /* draw dragging */

        if (hand_buffer != NONE) {
            Texture2D piece_texture =  piece_to_pic(hand_buffer,  wP,  wK,  wQ,  wB,  wN,  wR,  bK,  bQ,  bB,  bN,  bR,  bP,blank);
            DrawTexture(piece_texture,mousePoint.x - SQUARE_WIDTH / 2,mousePoint.y - SQUARE_HEIGHT / 2, WHITE);
        }

        /* Listen for keys */
        ListenForKeys(chess_board, &hand_buffer, &flip);

        /* Draw placements */
        DrawPlacement(chess_board, squareState, &hand_buffer,board_origin_x,board_origin_y,wP,  wK,  wQ,  wB,  wN,  wR,  bK,  bQ,  bB,  bN,  bR,  bP,  blank);

    



EndDrawing();
//----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
CloseWindow();        // Close window and OpenGL context
                      //--------------------------------------------------------------------------------------

return EXIT_SUCCESS;
}
