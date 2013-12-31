// DrawingDLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "DrawingDLL.h"
#include <stdexcept>

/** Function takes radius of circle to draw.
    * Returns vector of strings - grid with circle.
    * '.' stands for empty cell, '#' - for circle cell.
    */
void drawCircle(HDC hdc, int x0, int y0, int radius) {
    /* Initial coordinates to draw */
    int x = 0;
    int y = radius;
    /* Delta length from diagonal point to circle */
    int delta = 2 * (1 - radius);
    while(y >= 0) {
        /* Draw current point with appropriate mirror images */
        SetPixel(hdc, x0 + x, y0 + y, RGB(255, 0, 0));
        SetPixel(hdc, x0 + x, y0 - y, RGB(255, 0, 0));
        SetPixel(hdc, x0 - x, y0 + y, RGB(255, 0, 0));
        SetPixel(hdc, x0 - x, y0 - y, RGB(255, 0, 0));
        /* Delta value of length to circle of diagonal point and gorizontal one */
        int error = 2 * (delta + y) - 1;
        /* if diagonal is inside circle and gorizontal is nearer than diagonal */
        if (delta < 0 && error <= 0) {
            /* move in gorizontal way and update delta error of deiagonal point */
            ++x;
            delta += 2 * x + 1;
            continue;
        }
        error = 2 * (delta - x) - 1; 
        /* if diagonal is outside circle and is farer than vertical */
        if (delta > 0 && error > 0) {
            y--;
            delta += 1 - 2 * y;
            continue;
        }
        /* else go diagonal */
        x++;
        delta += 2 * (x - y);
        y--;
    }
}
