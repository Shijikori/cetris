#pragma once
#include <GL/gl.h>

// Color struct to store color data
struct color
{
    float red;
    float green;
    float blue;
    float alpha = 1.0;
    // constructor
    color(float r, float g, float b, float a=1.0)
    {
        red = r;
        green = g;
        blue = b;
        alpha = a;
    }
};

// Draw a quad
void drawQuad(float x, float y, float w, float h, color color)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glColor4f(color.red, color.green, color.blue, color.alpha);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
    glEnd();
}

// Draw a square
void drawSquare(float x, float y, float size, color color)
{
    drawQuad(x,y,size,size,color);
}