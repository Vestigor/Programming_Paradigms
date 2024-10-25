/***********************************************************
* File:     Gomoku
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: 五子棋大脑程序
* Date:     2024.10.24
* Update:   2024.10.24
***********************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>


#define true 1
#define false 0

#define BOARD_SIZE 12
#define MAX_SCORE 1000000000
#define MIN_SCORE -1000000000
#define MAX_DEPTH 3

#define DEBUG 0

#define EVEN_FIVE 100000000
#define LIVE_FOUR 10000000
#define RUSH_FOUR 1000000
#define LIVE_THREE 100000
#define SLEEP_THREE 10000
#define LIVE_TWO 1000
#define SLEEP_TWO 100


/***********************************************************
* Enum Name:   Cell
* Description: Used to represent the state of each cell on
*              the board (EMPTY, BLACK, or WHITE).
***********************************************************/
typedef enum { EMPTY, BLACK, WHITE } Cell;
/***********************************************************
* Struct Name: Piece
* Description: Stores the position of a piece on the board.
***********************************************************/
typedef struct {
    int x;
    int y;
}Piece;

Cell my_chess_piece;// Stores the AI's chess color (BLACK/WHITE)
Cell enemy_chess_piece;// Stores the opponent's chess color
Cell chess_board[BOARD_SIZE][BOARD_SIZE] = { EMPTY };//Stores the game state in a 12x12 board
int weighting_score[BOARD_SIZE][BOARD_SIZE];// A matrix used for positional scoring

/***********************************************************
* Function Name:   CreatPiece
* Function:        Initializes a piece with given coordinates
* Input Parameter:
*   - x: x-coordinate of the piece
*   - y: y-coordinate of the piece
* Returned Value:  A Piece object
***********************************************************/
Piece CreatPiece(int x, int y)
{
    Piece p;
    p.x = x;
    p.y = y;
    return p;
}

/***********************************************************
* Function Name:   PrintBoard
* Function:        Prints the current state of the chess board.
*                  This is for debugging purposes.
***********************************************************/
void PrintBoard() {
#ifdef DEBUG
    printf(" ");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%5d", i);  // Prints column numbers
        fflush(stdout);
    }
    printf("\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%2d ", i);  // Prints row numbers
        fflush(stdout);
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (chess_board[i][j] == BLACK) {
                printf("  ○ "); // Black piece
                fflush(stdout);
            }
            else if (chess_board[i][j] == WHITE) {
                printf("  ● ");  // White piece
                fflush(stdout);
            }
            else {
                printf(" EMP ");  // Empty cell
                fflush(stdout);
            }
        }
        printf("\n");
    }
    printf("\n");
#endif
}


/***********************************************************
* Function Name:   ConsecutiveEvaluate
* Function:        Counts consecutive pieces of a given player
*                  in a specific direction (dx, dy) from a
*                  starting position (x, y).
* Input Parameter:
*   - x, y: Coordinates of the starting position
*   - dx, dy: Direction vector
*   - player: Player (BLACK or WHITE)
* Returned Value:  The number of consecutive pieces in that direction
***********************************************************/
int ConsecutiveEvaluate(int x, int y, int dx, int dy, Cell player) {
    int count = 0;
    for (int i = 0; i < 5; i++) {
        int nx = x + i * dx;
        int ny = y + i * dy;
        if (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE && chess_board[nx][ny] == player)
            count++;
        else 
            break;
    }
    return count;
}

/***********************************************************
* Function Name:   DirectionEvaluate
* Function:        Evaluates the board score for a given player
*                  by looking in a specific direction (dx, dy).
* Input Parameter:
*   - x, y: Coordinates of the starting position
*   - dx, dy: Direction vector
*   - player: Player (BLACK or WHITE)
* Returned Value:  The score for the direction based on the
*                  number of consecutive pieces.
***********************************************************/
int DirectionEvaluate(int x, int y, int dx, int dy, Cell player) {
    int score = 0;
    int consecutive = ConsecutiveEvaluate(x, y, dx, dy, player);

    // Score based on the number of consecutive pieces
    if (consecutive == 5) {
        score += EVEN_FIVE;  // Five in a row, win
    }
    else if (consecutive == 4) {
        // Evaluate four
        if ((x - dx >= 0 && y - dy >= 0 && chess_board[x - dx][y - dy] == EMPTY) &&
            (x + 4 * dx < BOARD_SIZE && y + 4 * dy < BOARD_SIZE && chess_board[x + 4 * dx][y + 4 * dy] == EMPTY)) {
            score += LIVE_FOUR;  // Live four
        }
        else if((x - dx >= 0 && y - dy >= 0 && chess_board[x - dx][y - dy] == EMPTY)|| 
            (x + 4 * dx < BOARD_SIZE && y + 4 * dy < BOARD_SIZE && chess_board[x + 4 * dx][y + 4 * dy] == EMPTY))
            score += RUSH_FOUR;   // Rush four
    }
    else if (consecutive == 3) {
        if((x + 4 * dx < BOARD_SIZE && y +  4 * dy < BOARD_SIZE && chess_board[x + 4 * dx][y + 4 * dy] == player && chess_board[x + 3 * dx][y + 3 * dy] == EMPTY)&&
           (x - dx >= 0 && y - dy >= 0 && chess_board[x - dx][y - dy] == EMPTY|| x + 5 * dx < BOARD_SIZE && y + 5 * dy < BOARD_SIZE && chess_board[x + 5 * dx][y + 5 * dy] == EMPTY)||
           (x - 2*dx >= 0 && y - 2 *dy >= 0 && chess_board[x - 2 * dx][y - 2 * dy] == player&& chess_board[x -  dx][y - dy]==EMPTY)&&
           (x - 3*dx >= 0 && y - 3*dy >= 0 && chess_board[x - 3*dx][y - 3*dy] == EMPTY || x + 3 * dx < BOARD_SIZE && y + 3 * dy < BOARD_SIZE && chess_board[x + 3 * dx][y + 3 * dy] == EMPTY))
            score += RUSH_FOUR;  // 11101Jump rush four

        // Evaluate three
        else if ((x - dx >= 0 && y - dy >= 0 && chess_board[x - dx][y - dy] == EMPTY) &&
            (x + 3 * dx < BOARD_SIZE && y + 3 * dy < BOARD_SIZE && chess_board[x + 3 * dx][y + 3 * dy] == EMPTY))
            score += LIVE_THREE;   // Live three
        else if((x - dx >= 0 && y - dy >= 0 && chess_board[x - dx][y - dy] == EMPTY) ||
            (x + 3 * dx < BOARD_SIZE && y + 3 * dy < BOARD_SIZE && chess_board[x + 3 * dx][y + 3 * dy] == EMPTY))
            score += SLEEP_THREE;    // Sleep three
    }
    else if (consecutive == 2) {
        if((x + 4 * dx < BOARD_SIZE && y + 4 * dy < BOARD_SIZE && chess_board[x + 3 * dx][y + 3 * dy] == player && chess_board[x + 3 * dx][y + 3 * dy] == player && chess_board[x + 2 * dx][y + 2 * dy] == EMPTY))
            score += RUSH_FOUR;   // 11011Jump rush four
        else if((x + 3 * dx < BOARD_SIZE && y + 3 * dy < BOARD_SIZE && chess_board[x + 3 * dx][y + 3 * dy] == player && chess_board[x + 2 * dx][y + 2 * dy] == EMPTY) &&
            (x - dx >= 0 && y - dy >= 0 && chess_board[x - dx][y - dy] == EMPTY && x + 4 * dx < BOARD_SIZE && y + 4 * dy < BOARD_SIZE && chess_board[x + 4 * dx][y + 4 * dy] == EMPTY) ||
            (x - 2 * dx >= 0 && y - 2 * dy >= 0 && chess_board[x - 2 * dx][y - 2 * dy] == player && chess_board[x - dx][y - dy] == EMPTY) &&
            (x - 3 * dx >= 0 && y - 3 * dy >= 0 && chess_board[x - 3 * dx][y - 3 * dy] == EMPTY && x + 2 * dx < BOARD_SIZE && y + 2 * dy < BOARD_SIZE && chess_board[x + 2 * dx][y + 2 * dy] == EMPTY))
            score += LIVE_THREE;   // 1101Jump live three
        else if((x + 3 * dx < BOARD_SIZE && y + 3 * dy < BOARD_SIZE && chess_board[x + 3 * dx][y + 3 * dy] == player && chess_board[x + 2 * dx][y + 2 * dy] == EMPTY) &&
            (x - dx >= 0 && y - dy >= 0 && chess_board[x - dx][y - dy] == EMPTY || x + 4 * dx < BOARD_SIZE && y + 4 * dy < BOARD_SIZE && chess_board[x + 4 * dx][y + 4 * dy] == EMPTY) ||
            (x - 2 * dx >= 0 && y - 2 * dy >= 0 && chess_board[x - 2 * dx][y - 2 * dy] == player && chess_board[x - dx][y - dy] == EMPTY) &&
            (x - 3 * dx >= 0 && y - 3 * dy >= 0 && chess_board[x - 3 * dx][y - 3 * dy] == EMPTY || x + 2 * dx < BOARD_SIZE && y + 2 * dy < BOARD_SIZE && chess_board[x + 2 * dx][y + 2 * dy] == EMPTY))
            score += SLEEP_THREE;    // 1101Jump sleep three

        // Evaluate two
        else if ((x - dx >= 0&& y - dy >= 0 &&chess_board[x - dx][y - dy] == EMPTY) &&
            (x + 2 * dx < BOARD_SIZE && y + 2 * dy < BOARD_SIZE && chess_board[x + 2 * dx][y + 2 * dy] == EMPTY))
            score += LIVE_TWO;    // Live two
        else if ((x - dx >= 0 && y - dy >= 0 && chess_board[x - dx][y - dy] == EMPTY) ||
            (x + 2 * dx < BOARD_SIZE && y + 2 * dy < BOARD_SIZE && chess_board[x + 2 * dx][y + 2 * dy] == EMPTY))
            score += SLEEP_TWO;     // Sleep two
    }
    else if (consecutive == 1) {
        if((x + 4 * dx < BOARD_SIZE && y + 4 * dy < BOARD_SIZE && chess_board[x + 2 * dx][y + 2 * dy] == player && chess_board[x + 4 * dx][y + 4 * dy] == player &&
           chess_board[x + dx][y + dy] == EMPTY&& chess_board[x + 3 * dx][y + 3 * dy] == EMPTY) &&
           (x - dx >= 0 && y - dy >= 0 && chess_board[x - dx][y - dy] == EMPTY && x + 5 * dx < BOARD_SIZE && y + 5 * dy < BOARD_SIZE && chess_board[x + 5 * dx][y + 5 * dy] == EMPTY))
           score += SLEEP_THREE;    // 10101Jump sleep three
        else if((x + 2 * dx < BOARD_SIZE && y + 2 * dy < BOARD_SIZE && chess_board[x + 2 * dx][y + 2 * dy] == player && chess_board[x + dx][y + dy] == EMPTY) &&
            (x - dx >= 0 && y - dy >= 0 && chess_board[x - dx][y - dy] == EMPTY && x + 3 * dx < BOARD_SIZE && y + 3 * dy < BOARD_SIZE && chess_board[x + 3 * dx][y + 3 * dy] == EMPTY))
            score += LIVE_TWO;    // 101Jump live two
        else if ((x + 3 * dx < BOARD_SIZE && y + 3 * dy < BOARD_SIZE && chess_board[x + 3 * dx][y + 3 * dy] == player && chess_board[x + dx][y + dy] == EMPTY&& chess_board[x + 2 * dx][y + 2 * dy] == EMPTY) &&
            (x - dx >= 0 && y - dy >= 0 && chess_board[x - dx][y - dy] == EMPTY && x + 4 * dx < BOARD_SIZE && y + 4 * dy < BOARD_SIZE && chess_board[x + 3 * dx][y + 3 * dy] == EMPTY))
            score += LIVE_TWO;    // 1001Big jump live two
    }
    return score;
}

/***********************************************************
* Function Name:   MainEvaluate
* Function:        Main function for evaluating the
*                  board from both player's perspective.
* Returned Value:  Total score for the current board state
***********************************************************/
int MainEvaluate() {
    int score = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (chess_board[i][j] == my_chess_piece) {
                // check four directions:landscape,portrait,lower right oblique line,lower left oblique line
                score += DirectionEvaluate(i, j, 1, 0, my_chess_piece);  // landscape
                score += DirectionEvaluate(i, j, 0, 1, my_chess_piece);  // portrait
                score += DirectionEvaluate(i, j, 1, 1, my_chess_piece);  // lower right oblique line
                score += DirectionEvaluate(i, j, 1, -1, my_chess_piece); // lower left oblique line
            }
            if (chess_board[i][j] == enemy_chess_piece) {
                // check four directions:landscape,portrait,lower right oblique line,lower left oblique line
                score -= DirectionEvaluate(i, j, 1, 0, enemy_chess_piece);  // portrait
                score -= DirectionEvaluate(i, j, 0, 1, enemy_chess_piece);  // portrait
                score -= DirectionEvaluate(i, j, 1, 1, enemy_chess_piece);  // lower right oblique line
                score -= DirectionEvaluate(i, j, 1, -1, enemy_chess_piece); // lower left oblique line
            }
        }

    }
    return score;
}

/***********************************************************
* Function Name:   MakeMove
* Function:        Places a piece for a player on the board.
* Input Parameter:
*   - piece: Piece structure with coordinates
*   - player: Player making the move (BLACK/WHITE)
***********************************************************/
void MakeMove(const Piece piece, Cell player) {
    chess_board[piece.x][piece.y] = player;
}

/***********************************************************
* Function Name:   UndoMove
* Function:        Removes a piece from the board.
* Input Parameter:
*   - piece: Piece structure with coordinates to be cleared
***********************************************************/
void UndoMove(const Piece piece) {
    chess_board[piece.x][piece.y] = EMPTY;
}

/***********************************************************
* Function Name:   IsGameOver
* Function:        Checks if the game is over (5 in a row).
* Returned Value:  True if the game is over, otherwise false
***********************************************************/
int IsGameOver() {
    for (int i = 0; i <= BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (chess_board[i][j] != EMPTY) {
                if (ConsecutiveEvaluate(i, j, 1, 0, chess_board[i][j]) == 5)
                    return true;  // landscape
                if (ConsecutiveEvaluate(i, j, 0, 1, chess_board[i][j]) == 5)
                    return true; // portrait
                if (ConsecutiveEvaluate(i, j, 1, 1, chess_board[i][j]) == 5)
                    return true; // lower right oblique line
                if (ConsecutiveEvaluate(i, j, 1, -1, chess_board[i][j]) == 5)
                    return true;// lower left oblique line
            }

    return false;
}

/***********************************************************
* Function Name:   GetValidMoves
* Function:        Get all valid empty positions on the current board and return them
* Input Parameter:
*   - pieces: An array to store the valid positions
* Returned Value:  The number of valid moves
***********************************************************/
int  GetValidMoves(Piece pieces[BOARD_SIZE * BOARD_SIZE]) {
    int move_count = 0;
    // Iterate through the board to find all empty squares
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            // If the current position is empty, it's a valid move
            if (chess_board[i][j] == EMPTY) {
                pieces[move_count].x = i;
                pieces[move_count].y = j;
                move_count++;
            }
        }
    }
    return move_count;
}

/***********************************************************
* Function Name:   AlphaBeta
* Function:        Implementation of the Alpha-Beta pruning algorithm
*                  to optimize minimax search.
* Input Parameters:
*   - depth: The current depth of the search tree
*   - alpha: The best value that the maximizer can guarantee at this level
*   - beta: The best value that the minimizer can guarantee at this level
*   - isMaximizingPlayer: A flag to determine if it's the maximizer's turn
* Returned Value:  The best evaluated value of the board
***********************************************************/
int AlphaBeta(Cell player, int depth, int alpha, int beta) {
    // Base case: if maximum depth is reached or game is over
    if (depth == 0  || IsGameOver()) {
        return MainEvaluate();  
    }
    // Array to store all valid moves
    Piece pieces[BOARD_SIZE * BOARD_SIZE];
    int move_count = GetValidMoves(pieces);

    if (player == my_chess_piece) {  // AI最大化得分
        int max_temp_score = MIN_SCORE;
        for (int i = 0; i < move_count; i++) {
            // Simulate move for the maximizing player
            MakeMove(pieces[i], player);
            int temp_score = AlphaBeta(enemy_chess_piece, depth - 1, alpha, beta);
            UndoMove(pieces[i]);
            if (temp_score > max_temp_score)
                max_temp_score = temp_score;
            if (temp_score > alpha)
                alpha = temp_score;
            // Pruning
            if (beta <= alpha) break;
        }
        return max_temp_score;
    }
    else {
        int min_temp_score = MAX_SCORE;
        for (int i = 0; i < move_count; i++) {
            // Simulate move for the minimizing player
            MakeMove(pieces[i], player);
            int temp_score = AlphaBeta(my_chess_piece, depth - 1, alpha, beta);
            UndoMove(pieces[i]);
            if (temp_score < min_temp_score)
                min_temp_score = temp_score;
            if (temp_score < beta)
                beta = temp_score;
            // Pruning
            if (beta <= alpha) break;
        }
        return min_temp_score;
    }
}

/***********************************************************
* Function Name:   FindBestMove
* Function:        Determines the best move for the current player using
*                  the Alpha-Beta pruning algorithm.
* Input Parameters:
*   - depth: The depth limit for the search
* Returned Value:  The best move found by Alpha-Beta search
***********************************************************/
Piece FindBestMove() {
    int best_score = MIN_SCORE;
    Piece pieces[BOARD_SIZE * BOARD_SIZE], best_piece={ -1,-1 };
    int move_count = GetValidMoves(pieces);

    // Loop through each valid move to evaluate its potential
    for (int i = 0; i < move_count; i++) {
        // Simulate the move
        MakeMove(pieces[i], my_chess_piece);
        // Evaluate the move using Alpha-Beta with the opponent as the minimizing player
        int score = AlphaBeta(enemy_chess_piece, MAX_DEPTH-1,MIN_SCORE,MAX_SCORE);
        score += weighting_score[pieces[i].x][pieces[i].y];
        // Undo the move after evaluation
        UndoMove(pieces[i]);
        // If this move's evaluation is better than the current best, update the best move
        if (score > best_score) {
            best_score = score;
            best_piece = pieces[i];
        }
    }
    return best_piece;// Return the move that leads to the best evaluation
}

/***********************************************************
* Function Name:   InitialWeightingScore
* Function:        Calculates the initial weighting score for the board,
*                  giving each piece a score based on its position and type.
*                  This function is used to give an initial evaluation of the board.
* Input Parameters: None
* Returned Value:   The overall weighting score of the board
***********************************************************/
void InitialWeightingScore()
{
    int start = 0;   // The position where the outer ring starts
    int end = BOARD_SIZE - 1; // The position where the outer ring ends
    int value = 1;   // The initial value to fill

    while (start <= end) {
        // Top from left to right
        for (int i = start; i <= end; i++) {
            weighting_score[start][i] = value;
        }

        // Right side from top to bottom
        for (int i = start + 1; i <= end; i++) {
            weighting_score[i][end] = value;
        }

        // bottom from right to left
        for (int i = end - 1; i >= start; i--) {
            weighting_score[end][i] = value;
        }

        // Left side from bottom to top
        for (int i = end - 1; i > start; i--) {
            weighting_score[i][start] = value;
        }

        // The inner ring is assigned an increasing value
        start++;
        end--;
        value++;
    }      
}

/***********************************************************
* Function Name: Start
* Function:      Initializes the game by setting up the pieces and
*                determining which side the player will control. The game
*                starts with predefined moves on the board.
* Input Parameters: None
* Returned Value:   None
***********************************************************/
void Start()
{
    int chess_piece;
    scanf(" %d", &chess_piece);

    // Set player and AI pieces based on the player's selection
    if (chess_piece == 1) {
        my_chess_piece = BLACK;
        enemy_chess_piece = WHITE;
    }
    else {
        my_chess_piece = WHITE;
        enemy_chess_piece = BLACK;
    }

    // Initialize the weighting score for the initial board state
    InitialWeightingScore();

    // Predefined moves to set up the initial board state
    Piece piece = CreatPiece(5, 5);
    MakeMove(piece, WHITE);
    piece = CreatPiece(6, 6);
    MakeMove(piece, WHITE);
    piece = CreatPiece(5, 6);
    MakeMove(piece, BLACK);
    piece = CreatPiece(6, 5);
    MakeMove(piece, BLACK);

    // Output a confirmation message that the game has started
    printf("OK\n");
    fflush(stdout);
}

/***********************************************************
* Function Name: Place
* Function:      Receives the player's move and places their piece on the board.
* Input Parameters: None
* Returned Value:   None
***********************************************************/
void Place()
{
    Piece piece;
    // Receive the x and y coordinates of player
    scanf("%d %d", &piece.x, &piece.y);

    // Place the player's piece on the board
    MakeMove(piece, enemy_chess_piece);
}

/***********************************************************
* Function Name: Turn
* Function:      Executes the AI's turn. The AI calculates the best move using
*                the FindBestMove function and places its piece on the board.
* Input Parameters: None
* Returned Value:   None
***********************************************************/
void Turn()
{
    // The AI calculates its best move
    Piece piece= FindBestMove();
    // Execute the move on the board
    MakeMove(piece, my_chess_piece);
    // Output the AI's move to the console
    printf("%d %d\n", piece.x, piece.y);
    fflush(stdout);
}

/***********************************************************
* Function Name: End
* Function:      Receives the result of the game (win/loss/draw) from the server
*                and ends the game.
* Input Parameters: None
* Returned Value:   None
***********************************************************/
void End()
{
    int result;
    // Get the result of the game 
    scanf(" %d", &result);
}

/***********************************************************
* Function Name: main
* Function:      Main game loop that continuously listens for input commands from
*                the server and executes the appropriate functions to handle the game flow.
* Input Parameters: None
* Returned Value:   int (returns 0 upon successful completion)
***********************************************************/
int main()
{
    while (true) {
        char hint[10];
#ifdef DEBUG
        time_t t = time(NULL);
        char* ct = NULL;
        ct = ctime(&t);
        printf("%s", ct);
        fflush(stdout);
#endif
        // Wait for input commands (START, PLACE, TURN, END) from the server
        scanf("%s", hint);
        if (!strcmp(hint, "START")) {
            Start();
#ifdef DEBUG
            printf("Game started!\n");
            fflush(stdout);
#endif
        }
        else if (!strcmp(hint, "PLACE")) {
            Place();
#ifdef DEBUG
            printf("Placed enemy piece on board:\n");
            fflush(stdout);
            PrintBoard();
#endif
        }
        else if (!strcmp(hint, "TURN")) {
#ifdef DEBUG
            clock_t startTime = clock();
#endif
            Turn();
#ifdef DEBUG
            clock_t endTime = clock();
            printf("\nRun time is %ldms\n", endTime - startTime);
            fflush(stdout);
            printf("AI made its move:\n");
            fflush(stdout);
            PrintBoard();
#endif
        }
        else if (!strcmp(hint, "END")) { 
            End();
            break;
        }
    }

    return 0;
}