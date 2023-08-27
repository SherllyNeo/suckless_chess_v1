#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chess.h"
#include "shared.h"

#define HISTORY_SIZE 100

int main(int argc, char *argv[])
{
    char* fen_string = NULL;
    /* get args */
    for (int a = 0; a<argc; a++) {
        if (!strcmp(argv[a],"--fen")) {
            fen_string = argv[++a];
        }
    }


    const int screenWidth = 500;
    const int screenHeight = 500;
    chess_square chess_board[BOARD_WIDTH][BOARD_HEIGHT];
    chess_square chess_board_history[HISTORY_SIZE][BOARD_WIDTH][BOARD_HEIGHT];
    int history_len = 0;
    int history_index = 0;
    float board_origin_x = screenWidth / 2 + SQUARE_WIDTH;
    float board_origin_y = screenHeight / 2;


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
    if (fen_string) {
        parse_fen(chess_board,fen_string);
    }
    else {
        ResetBoard(chess_board);
    }

    memcpy(chess_board_history[0],chess_board,sizeof(chess_board));

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
    int flipped = 0;
    int change_flag = 1;

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
                    if (hand_buffer != NONE)
                    {
                        change_flag = 1;
                        if (history_index < history_len)
                            history_len = history_index;
                    }
                }
                else if (CheckCollisionPointRec(mousePoint,chess_square_as_rec) && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                    if (chess_board[x][y].piece != NONE)
                    {
                        change_flag = 1;
                        if (history_index < history_len)
                            history_len = history_index;
                    }
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
            chess_square tmp[8][8];
            for(int i = 0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    tmp[i][j] = chess_board[8-i-1][8-j-1];
                }
            }

            memcpy(chess_board,tmp,sizeof(tmp));

            flipped = 1 - flipped;
            flip = 0;
        }
        DrawBoard(board_origin_x,board_origin_y,chess_board,show_names,numbers,letters,wP,  wK,  wQ,  wB,  wN,  wR,  bK,  bQ,  bB,  bN,  bR,  bP,  blank);

        /* toggle show names flag */
        if (IsKeyPressed(KEY_SPACE)) 
            show_names = !show_names;

        /* DRAW */
        BeginDrawing();
        DrawText("Simple Chess",screenWidth / 2, 0, TITLE_SIZE, BLACK);

        ClearBackground(BROWN);


        /* draw dragging */

        if (hand_buffer != NONE) {
            Texture2D piece_texture =  piece_to_pic(hand_buffer,  wP,  wK,  wQ,  wB,  wN,  wR,  bK,  bQ,  bB,  bN,  bR,  bP,blank);
            DrawTexture(piece_texture,mousePoint.x - SQUARE_WIDTH / 2,mousePoint.y - SQUARE_HEIGHT / 2, WHITE);
        }

        /* Listen for keys */
        ListenForKeys(chess_board, chess_board_history,history_len,&history_index,&hand_buffer, &flip);

        /* Draw placements */
        DrawPlacement(chess_board, squareState, &hand_buffer,board_origin_x,board_origin_y,wP,  wK,  wQ,  wB,  wN,  wR,  bK,  bQ,  bB,  bN,  bR,  bP,  blank);

        /* draw FEN */
        char fen_string[100];
        chess_square chess_board_cpy[8][8];
        memcpy(chess_board_cpy,chess_board,sizeof(chess_board));
        board_to_fen(chess_board_cpy,fen_string,flipped,history_len);

        DrawText(fen_string, board_origin_x, board_origin_y + BOARD_HEIGHT*SQUARE_HEIGHT + SQUARE_HEIGHT * 2, 20, BLACK);


        EndDrawing();
        /* save if any changes */
        if (change_flag) {
             history_len = (history_len + 1) % HISTORY_SIZE; 
             history_index = history_len;
             memcpy(chess_board_history[history_len],chess_board,sizeof(chess_board));
            change_flag = 0;
         }

        // De-Initialization
        //--------------------------------------------------------------------------------------
                              //--------------------------------------------------------------------------------------

    }
    CloseWindow();        // Close window and OpenGL context
    return EXIT_SUCCESS;
}
