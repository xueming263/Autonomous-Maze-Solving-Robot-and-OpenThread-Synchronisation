#include <stdio.h>
#include <string.h>
#include "path.h"


// dir is current turning direction（'L', 'S', 'R', 'B'）
void record_path(char dir)
{
    if (path_length < 256)
    {
        path[path_length] = dir; // recording path (turning direction)
        path_length++;           // update path length (number of intersections)
    }
}

// overwrite the turning direction char when meet dead end
char simplify_char(char x, char y)
{
    if (x == 'L' && y == 'L') return 'S'; // L B L → S
    if (x == 'L' && y == 'R') return 'B'; // L B R → B
    if (x == 'L' && y == 'S') return 'R'; // L B S → R

    if (x == 'R' && y == 'L') return 'B'; // R B L → B
    if (x == 'R' && y == 'R') return 'S'; // R B R → S
    if (x == 'R' && y == 'S') return 'L'; // R B S → L

    if (x == 'S' && y == 'L') return 'R'; // S B L → R
    if (x == 'S' && y == 'R') return 'L'; // S B R → L
    if (x == 'S' && y == 'S') return 'B'; // S B S → B

    // There should be no other situations. If you encounter 
    // them, you can customize the process.
    return '?';
}

void simplify_path(void)
{
    char stack[256];
    unsigned int top = 0;

    for (unsigned int i = 0; i < path_length; i++)
    {
        stack[top++] = path[i];

        // check if X B Y mode
        while (top >= 3)
        {
            char X = stack[top - 3];
            char B = stack[top - 2];
            char Y = stack[top - 1];

            if (B == 'B' &&
                (X == 'L' || X == 'R' || X == 'S') &&
                (Y == 'L' || Y == 'R' || Y == 'S'))
            {
                char new_char = simplify_char(X, Y);
                // overwrite X position with new character
                stack[top - 3] = new_char;
                // stack out B, Y
                top -= 2;
            }
            else
            {
                // break loop if no match
                break;
            }
        }
    }

    // write simplified path content back to array
    for (unsigned int i = 0; i < top; i++)
    {
        path[i] = stack[i];
    }
    path[top] = '\0';
    path_length = top;
}