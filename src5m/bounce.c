/**
 * bounce.c
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Edited By Zach Toolson
 * zach.toolson@gmail.com
 * Bounces a circle back and forth in a window.
 * 
 * Zach added y_direction movement and bouncing off the top and bottom edges
 */

// standard libraries
#include <stdio.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

int main(void)
{
    // instantiate window
    GWindow window = newGWindow(320, 240);

    // instantiate circle
    GOval circle = newGOval(0, 110, 20, 20);
    setColor(circle, "BLACK");
    setFilled(circle, true);
    add(window, circle);
    
    // initial velocity
    double x_velocity = 2.0;
    double y_velocity = 2.0;
    
    // bounce forever
    while (true)
    {
        // move circle along
        move(circle, x_velocity, y_velocity);

        // bounce off right edge of window
        // NOTE: measure cirlce from top left, so we need to add width of circle
        if (getX(circle) + getWidth(circle) >= getWidth(window))
        {
            x_velocity = -x_velocity;
        }

        // bounce off left edge of window
        else if (getX(circle) <= 0)
        {
            x_velocity = -x_velocity;
        }

        // bounce off bottom edge of window
        if (getY(circle) + getWidth(circle) >= getHeight(window))
        {
            y_velocity = -y_velocity;
        }
        // bounce off the top edge of the window
        else if (getY(circle) <= 0)
        {
            y_velocity = -y_velocity;
        }

        // linger before moving again
        pause(10);
    }
}
