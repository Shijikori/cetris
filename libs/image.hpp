#pragma once
#include <GL/gl.h>
#include <cstring>
#include <fstream>

// Generate a bitmap. Takes width, height and a memory pointer.
void genBitmap(int width, int height, GLubyte *&mem)
{
    if (!mem) std::free(mem);
    mem = new GLubyte[width * height * 3];
    
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int pos = (x + y * width) * 3;
            /*
            RED
            GREEN
            BLUE
            */
            mem[pos    ] = (255 - (x % 255)) * (255.0/width);
            mem[pos + 1] = (255 - ((x * y) % 255)) * (255.0/width);
            mem[pos + 2] = (y % 255) * (255.0/width);
        }
    }
    std::cout << "bitmap complete!\n"; // debug
}

// Load a PPM file.
void loadPPM(std::string img, GLubyte *&mem)
{
    /*
    TODO: 
    - Read header to parse information.
    - Read pixel data as integers, put data in memory.
    */
   std::ifstream file(img, std::ios::binary);
}