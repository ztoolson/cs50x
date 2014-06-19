//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 8

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
GLabel initLivesLabel(GWindow window);
void updateLivesLabel(GWindow window, GLabel label, int lives);
void updateScoreboard(GWindow window, GLabel label, int points);
void checkWindowBounce(GWindow window, GOval ball, double* x_velocity_addr, double* y_velocity_addr);
void restartGame(GWindow window, GOval ball, double* x_velocity);
void movePaddle(GRect paddle);
void checkObjectCollision(GWindow window, GOval ball, GRect paddle, double* x_velocity, double* y_velocity, int* bricks);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // ************ SET UP GAME WINDOW *****************
    
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // ball inital velocity
    double x_velocity = drand48() * 2 + 1;
    double y_velocity = 2;

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);
    int paddle_y = getY(paddle);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel lives_label = initLivesLabel(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // User must click to start game
    waitForClick();

    // *****************PLAY GAME ******************

    // display default lives 
    updateLivesLabel(window, lives_label, lives);

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // update score 
        points = ((ROWS * COLS) - bricks) * 5;
        updateScoreboard(window, label, points);

        // move ball
        move(ball, x_velocity, y_velocity);

        // check for bounces off left, right, and top edges of game window
        checkWindowBounce(window, ball, &x_velocity, &y_velocity);

        // check bounce off bottom edge of window
        if (getY(ball) + getWidth(ball) >= getHeight(window))
        {
            // ***** LOSE A LIFE! *******
            lives--;
            updateLivesLabel(window, lives_label, lives);
            restartGame(window, ball, &x_velocity);
        }

        // linger before moving again
        pause(7);

        // Update paddle with mouse movement
        movePaddle(paddle);

        // Detect if ball collides with Brick or Paddle
        checkObjectCollision(window, ball, paddle, &x_velocity, &y_velocity, &bricks);
    }

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // Variables used to determine where bricks are.
    int x_space = 3;
    int y_space = 7;
    int current_x = 0;
    int current_y = 50;
    int brick_width = (WIDTH / COLS) - 2 * x_space; // Leave space for left and right of brick
    int brick_height = (HEIGHT / ROWS) / (ROWS * 2) ;
    int number_of_colors = 5;

    // Add colors to the blocks
    string colors[number_of_colors];
    colors[0] = "RED";
    colors[1] = "ORANGE";
    colors[2] = "YELLOW";
    colors[3] = "GREEN";
    colors[4] = "BLUE";

    // Add the bricks to the window
    for (int row = 0; row < ROWS; ++row)
    {
        for (int col = 0;  col < COLS; ++col)
        {
            // Add spacing to the left of the block
            current_x = current_x + x_space;
            
            // Create block and add to window
            GRect rect = newGRect(current_x, current_y, brick_width, brick_height);
            setFilled(rect, true);
            int color_index = row % number_of_colors; 
            setColor(rect, colors[color_index]); // Repeat the colors if more than 5 rows
            add(window, rect);
            
            // Add spacing to the right of the block
            current_x = current_x + brick_width + x_space;
        }
        // Add spacing between rows
        current_y = current_y + brick_height + y_space;
        current_x = 0; // Reset the x position
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // Variables used for ball
    int ball_width = (getWidth(window) / COLS) / 3; // ball size dependent on number of cols, ball is 3 times smaller than the bricks 
    int center_x = getWidth(window) / 2 - (ball_width / 2);
    int center_y = getHeight(window) / 2;
    
    // Create the ball
    GOval ball = newGOval(center_x, center_y, ball_width, ball_width);
    setFilled(ball, true);
    setColor(ball, "BLACK");

    // Add the ball to the center of screen
    add(window, ball);

    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // Variable used to build the paddle and place it
    int paddle_width = (getWidth(window) / COLS) * 2;
    int paddle_height = 10;
    int y_location = 500;
    int x_location = getWidth(window) / 2 - (paddle_width / 2);
    
    // Build the paddle
    GRect paddle = newGRect(x_location, y_location, paddle_width, paddle_height);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    
    // Put on window
    add(window, paddle);

    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // Make scoreboard
    GLabel scoreboard = newGLabel("BREAKOUT!");

    // Variables used for placing scoreboard
    double x = (getWidth(window) - getWidth(scoreboard)) / 2;
    double y = (getHeight(window) - getHeight(scoreboard)) / 2;
    setLocation(scoreboard, x, y);

    // Add scoreboard to window
    add(window, scoreboard);

    return scoreboard;
}

/**
 * Instantiates, configures, and returns label for lives.
 */
GLabel initLivesLabel(GWindow window)
{
    GLabel lives = newGLabel("Lives: 0");

    // Variables used for placing scoreboard
    double x = 10;
    double y = 20 ;
    setLocation(lives, x, y);

    // Add scoreboard to window
    add(window, lives);

    return lives;
}

/**
 * Updates lives's label.
 */
void updateLivesLabel(GWindow window, GLabel label, int lives)
{
    // update label
    char s[7 + 12]; // 7 for constance lives, and 12 for potentially a lot of lives...
    sprintf(s, "Lives: %i", lives);
    setLabel(label, s);
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}


/**
 * Update the x_velocity and y_velocity if the ball has bounced off the edge of the window
 */
void checkWindowBounce(GWindow window, GOval ball, double* x_velocity_addr, double* y_velocity_addr)
{

    // bounce off right edge of window
    // NOTE: measure ball from top left, so we need to add width of ball
    if (getX(ball) + getWidth(ball) >= getWidth(window))
    {
        *x_velocity_addr = -1 *  *x_velocity_addr;
    }
    // bounce off left edge of window
    else if (getX(ball) <= 0)
    {
        *x_velocity_addr = -1 *  *x_velocity_addr;
    }

    // bounce off the top edge of the window
    if (getY(ball) <= 0)
    {
        *y_velocity_addr = -1 * *y_velocity_addr;
    }
}

/**
 * Move the ball to center of screen, recalculate a random x_velocity,
 * and wait for user to click before playing again.
 */
void restartGame(GWindow window, GOval ball, double* x_velocity)
{
    // Move ball back to center
    int center_x = getWidth(window) / 2 - (getWidth(ball) / 2);
    int center_y = getHeight(window) / 2;
    setLocation(ball, center_x, center_y);

    // Recalculate a velocity for the ball
    srand48(time(NULL));
    double drand = drand48();
    *x_velocity = (drand * 2 + 1);
    // Add some randomness to the restart
    if (drand < 0.5)
    {
        *x_velocity = *x_velocity * -1;
    }
    
    // User must click to play again
    waitForClick();
}

/**
 * Move the paddle with the mouse movement
 */
void movePaddle(GRect paddle)
{
    // check for mouse event
    GEvent event = getNextEvent(MOUSE_EVENT);

    // if we heard one
    if (event != NULL)
    {
        // if the event was movement
        if (getEventType(event) == MOUSE_MOVED)
        {
            // Only update the x value
            double x = getX(event) - getWidth(paddle) / 2; // Subtract off the radius to center the ball 
            setLocation(paddle, x, getY(paddle));
        }
    }
}

/**
 * Check if the ball has collided with the paddle or a brick
 */
void checkObjectCollision(GWindow window, GOval ball, GRect paddle, double* x_velocity, double* y_velocity, int* bricks)
{
    GObject collision_object = detectCollision(window, ball);

    // Determine if the ball has collided with another object in the window
    if (collision_object != NULL)
    {
        // Ball collided with paddle
        if (collision_object == paddle)
        {
            *y_velocity = -1 * *y_velocity;
        }
        // Detected a Brick
        else if (strcmp(getType(collision_object), "GRect") == 0)
        {
            *y_velocity = *y_velocity * -1;
            removeGWindow(window, collision_object);
            *bricks = *bricks - 1;
        }
    }
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
