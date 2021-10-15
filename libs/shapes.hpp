#pragma once
#include <GL/gl.h>
#include "colour.hpp"

// Draw a triangle (needs improvement)
void drawTriangle()
{
    // TODO : Improve triangle drawing
    glBegin(GL_TRIANGLES);
        glColor4f(0.46, 0.1, 0.7, 0.93);
        glVertex2f(0, -0.5);
        glVertex2f(-0.4, 0.5);
        glVertex2f(0.4, 0.5);
    glEnd();
}

// Draw a quad
void drawQuad(float x, float y, float w, float h, Colour colour)
{
    glBegin(GL_QUADS);
        glColor4f(colour.red, colour.green, colour.blue, colour.alpha);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
    glEnd();
}

// Draw a square
void drawSquare(float x, float y, float size, Colour colour)
{
    drawQuad(x,y,size,size,colour);
}