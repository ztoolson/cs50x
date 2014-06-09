/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

// Current Blank Space location
int blank_row, blank_col;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            printf("Congratulations! You have won a difficult game.\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    int total_tiles = (d * d) - 1;
    
    // Fill the board counting backwards
    int current_tile = total_tiles;
    for(int row=0; row < d; ++row) {
        for(int col=0; col < d; ++col) {
            board[row][col] = current_tile;
            current_tile--;
        }
    }

    // If total tiles is odd, switch tile 2 and 1.
    // board[d-1][d-1] is the bottom right side of the board
    if (total_tiles % 2 != 0) {
        board[d-1][d-2] = 2;
        board[d-1][d-3] = 1;
    }

    // Update blank space
    blank_row = d-1;
    blank_col = d-1;
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for(int row=0; row < d; ++row) {
        for(int col=0; col < d; ++col) {
            // Replace 0 with _ for our board, otherwise print number
            if (board[row][col] == 0) {
                printf("%2c ", 95); // 95 is ascii num for '_'
            }
            else {
                printf("%2d ", board[row][col]);
            }
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    int target_row = -1;
    int target_col = -1;
    bool result = false;

    // Check 4 possible moves around the tile. First part of each statement
    // is to verify the access to the board is valid.
    if ( (blank_row + 1 < d) && board[blank_row + 1][blank_col] == tile ){ // Down
        target_row = blank_row + 1;
        target_col = blank_col;
    } 
    else if ( (blank_row -1 >= 0) && board[blank_row - 1][blank_col] == tile ) { // Up
        target_row = blank_row - 1;
        target_col = blank_col;
    }
    else if ( (blank_col + 1 < d) && board[blank_row][blank_col + 1] == tile ) { // Right
        target_row = blank_row;
        target_col = blank_col + 1;
    }
    else if ( (blank_row -1 >= 0) && board[blank_row][blank_col - 1] == tile ) { // Left
        target_row = blank_row;
        target_col = blank_col - 1;
    }

    if(target_row > -1 || target_col > -1) {
        // Move tile
        board[blank_row][blank_col] = tile;
        // Move blank
        board[target_row][target_col] = 0;

        // Update blank location
        blank_row = target_row;
        blank_col = target_col;

        result = true;
    }

     
    return result;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // TODO
    int count = 1;
    bool result = false;

    for(int row=0; row < d; ++row) {
        for (int col=0; col < d; ++col) {
            if (count == d*d){
                result=true;
            }
            else if (board[row][col] != count) {
                break;
            }
            count++;
        }
    }
    return result;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}
