/**
 *
 * cursor.c
 *
 * Zach Toolson 
 * zach.toolson@gmail.com 
 *
 * Draws a rectangle that follows user's cursor in the horizontal direction within a window.
 */

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

int main(void)
{

    // instantiate window
    GWindow window = newGWindow(320, 240);

    // instantiate rectangle
    int x = 0;
    int y = 240/2;
    int width = 100;
    int height = 50;
    GRect rect = newGRect(x, y, width, height);

    // fill the rectangle with red
    setFilled(rect, true);
    setColor(rect, "RED");

    // add rectangle to window
    add(window, rect);

    // follow mouse forever
    while (true)
    {
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we heard one
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure circle follows top cursor
                double x = getX(event) - getWidth(rect) / 2; // Subtract off the radius to center the circle
                // double y = getY(event) - getHeight(rect) / 2;
                setLocation(rect, x, y);
            }
        }
    }
}
