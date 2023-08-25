#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define SQUARE_WIDTH 60
#define SQUARE_HEIGHT 60

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8
#define AMOUNT_OF_CHESS_SQUARES BOARD_WIDTH * BOARD_HEIGHT

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

int main(void)
{
    const int screenWidth = 900;
    const int screenHeight = 900;
    chess_square chess_board[BOARD_WIDTH][BOARD_HEIGHT];
    float board_origin_x = screenWidth / 20;
    float board_origin_y = screenHeight / 5;

    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            chess_board[x][y].width = SQUARE_WIDTH;
            chess_board[x][y].height = SQUARE_HEIGHT;
            chess_board[x][y].row = y;
            chess_board[x][y].col = x;
            chess_board[x][y].piece = NONE;
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

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);    // Window configuration flags
    InitWindow(screenWidth, screenHeight, "Simple Chess");


    Texture2D wP = LoadTexture("./chess_pieces/wP.png");
    Texture2D wK = LoadTexture("./chess_pieces/wK.png");
    Texture2D wQ =  LoadTexture("./chess_pieces/wQ.png");
    Texture2D wB =  LoadTexture("./chess_pieces/wB.png");
    Texture2D wN =  LoadTexture("./chess_pieces/wN.png");
    Texture2D wR =  LoadTexture("./chess_pieces/wR.png");
    Texture2D bK =  LoadTexture("./chess_pieces/bK.png");
    Texture2D bQ =  LoadTexture("./chess_pieces/bQ.png");
    Texture2D bB =  LoadTexture("./chess_pieces/bB.png");
    Texture2D bN =  LoadTexture("./chess_pieces/bN.png");
    Texture2D bR =  LoadTexture("./chess_pieces/bR.png");
    Texture2D bP =  LoadTexture("./chess_pieces/bP.png");
    Texture2D blank =  LoadTexture("./chess_pieces/blank.png");
    wP.width = SQUARE_WIDTH - 2;
    wP.height = SQUARE_HEIGHT - 2;


    char* letters[8] = {"A","B","C","D","E","F","G","H"};
    char* numbers[8] = {"8","7","6","5","4","3","2","1"};
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    Vector2 mousePoint = { 0.0f, 0.0f };
    chess_piece hand_buffer = NONE;
    int squareState[BOARD_WIDTH][BOARD_HEIGHT] = { 0 };

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
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
                else  {
                    squareState[x][y] = 0;
                }
            }
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        DrawText("Simple Chess", screenWidth / 2, 0, 100, BLACK);

        ClearBackground(BROWN);
        int font_size = 45;

        for (int x = 0; x < BOARD_WIDTH; x++)
            DrawText(letters[x],board_origin_x + SQUARE_WIDTH*x + (SQUARE_WIDTH / 3), board_origin_y + SQUARE_HEIGHT*BOARD_HEIGHT, font_size, GRAY);

        for (int y = 0; y < BOARD_HEIGHT; y++)
            DrawText(numbers[y],board_origin_x + BOARD_WIDTH - SQUARE_WIDTH + 15,board_origin_y + SQUARE_HEIGHT*y + (SQUARE_HEIGHT / 3) - 10,font_size, GRAY);

        for (int y = 0; y < BOARD_HEIGHT; y++)
        {
            for (int x = 0; x < BOARD_WIDTH; x++)
            {
                chess_square cur_sqr = chess_board[x][y];
                DrawRectangle(board_origin_x + SQUARE_WIDTH*x, board_origin_y + SQUARE_HEIGHT*y, cur_sqr.width, cur_sqr.height, ( (cur_sqr.row % 2) == (cur_sqr.col %2) ) ? WHITE : BEIGE);
                if (cur_sqr.piece != NONE)   {
                    Texture2D piece_texture =  piece_to_pic(cur_sqr.piece,  wP,  wK,  wQ,  wB,  wN,  wR,  bK,  bQ,  bB,  bN,  bR,  bP,blank);
                    DrawTexture(piece_texture,board_origin_x + SQUARE_WIDTH*x, board_origin_y + SQUARE_WIDTH*y , WHITE);
                }
                
                if (IsKeyDown(KEY_SPACE))
                {
                    DrawRectangle(board_origin_x + SQUARE_WIDTH*x, board_origin_y + SQUARE_HEIGHT*y, cur_sqr.width, cur_sqr.height, ( (cur_sqr.row % 2) == (cur_sqr.col %2) ) ? WHITE : BEIGE);

                    char square_name[30];
                    sprintf(square_name,"%s%s",letters[x],numbers[y]);
                    DrawText(square_name,board_origin_x + SQUARE_WIDTH*x, board_origin_y + SQUARE_HEIGHT*y,SQUARE_WIDTH/2,GRAY);
                }

                if (IsKeyDown(KEY_Q))
                {
                        hand_buffer = W_QUEEN;
                }
                if (IsKeyDown(KEY_K))
                {
                        hand_buffer = W_KING;
                }
                if (IsKeyDown(KEY_P))
                {
                        hand_buffer = W_PAWN;
                }
                if (IsKeyDown(KEY_N))
                {
                        hand_buffer = W_KNIGHT;
                }
                if (IsKeyDown(KEY_R))
                {
                        hand_buffer = W_ROOK;
                }
                if (IsKeyDown(KEY_B))
                {
                        hand_buffer = W_BISHOP;
                }
                if (IsKeyDown(KEY_Q) && IsKeyDown(KEY_LEFT_SHIFT))
                {
                        hand_buffer = B_QUEEN;
                }
                if (IsKeyDown(KEY_K) && IsKeyDown(KEY_LEFT_SHIFT))
                {
                        hand_buffer = B_KING;
                }
                if (IsKeyDown(KEY_P) && IsKeyDown(KEY_LEFT_SHIFT))
                {
                        hand_buffer = B_PAWN;
                }
                if (IsKeyDown(KEY_N) && IsKeyDown(KEY_LEFT_SHIFT))
                {
                        hand_buffer = B_KNIGHT;
                }
                if (IsKeyDown(KEY_R) && IsKeyDown(KEY_LEFT_SHIFT))
                {
                        hand_buffer = B_ROOK;
                }
                if (IsKeyDown(KEY_B) && IsKeyDown(KEY_LEFT_SHIFT))
                {
                        hand_buffer = B_BISHOP;
                }
                if (IsKeyDown(KEY_C) && IsKeyDown(KEY_LEFT_SHIFT))
                {
                    for (int y = 0; y < BOARD_HEIGHT; y++)
                    {
                        for (int x = 0; x < BOARD_WIDTH; x++)
                        {
                            chess_board[x][y].piece = NONE;
                        }
                    }
                }

                if (IsKeyDown(KEY_C) && !IsKeyDown(KEY_LEFT_SHIFT))
                {
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


                if (hand_buffer != NONE) {
                    Texture2D piece_texture =  piece_to_pic(hand_buffer,  wP,  wK,  wQ,  wB,  wN,  wR,  bK,  bQ,  bB,  bN,  bR,  bP,blank);
                    DrawTexture(piece_texture,mousePoint.x - SQUARE_WIDTH / 2,mousePoint.y - SQUARE_HEIGHT / 2, WHITE);
                }

                if (squareState[x][y])
                {
                    if (cur_sqr.piece != NONE && hand_buffer == NONE) {
                        hand_buffer = chess_board[x][y].piece;
                        chess_board[x][y].piece = NONE;
                    }
                    else if (cur_sqr.piece != NONE && hand_buffer != NONE) {
                        chess_board[x][y].piece = hand_buffer;
                        hand_buffer = NONE;
                    }
                    else if (cur_sqr.piece == NONE && hand_buffer != NONE) {
                        chess_board[x][y].piece = hand_buffer;
                        hand_buffer = NONE;
                    }
                    else {
                        Texture2D piece_texture =  piece_to_pic(cur_sqr.piece,  wP,  wK,  wQ,  wB,  wN,  wR,  bK,  bQ,  bB,  bN,  bR,  bP,blank);
                        DrawTexture(piece_texture,board_origin_x + SQUARE_WIDTH*x, board_origin_y + SQUARE_WIDTH*y , WHITE);
                        hand_buffer = NONE;
                    }
                }
            }
        }

    EndDrawing();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
CloseWindow();        // Close window and OpenGL context
                      //--------------------------------------------------------------------------------------

return EXIT_SUCCESS;
}
