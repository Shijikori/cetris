#pragma once

/* Colour struct to store colour data.
Contructor takes float red, float green, float blue and float alpha values.*/
struct Colour
{
    float red;
    float green;
    float blue;
    float alpha = 1.0;
    // constructor
    Colour(float r, float g, float b, float a=1.0f)
    {
        red = r;
        green = g;
        blue = b;
        alpha = a;
    }
};