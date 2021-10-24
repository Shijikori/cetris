#pragma once
#include <GL/gl.h>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cstdint>

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
}

// Skips the comment lines of PPM headers, goes unti next non-comment line.
void skipCommentsPPM(std::ifstream &file, std::string &lineVar)
{
    /* skip comments loop */
    do
    {
        file >> lineVar;
        if (lineVar[0] == '#')
        {
            std::string comment;
            std::getline(file, comment);
            lineVar += comment;
        }
    } while (lineVar[0] == '#');
}

// Load a PPM file into memory. Loads only format P6.
void loadPPM(std::string imgPath, GLubyte *&mem, int *size)
{
    assert(imgPath != "\0");

    if (!mem) std::free(mem);

    std::ifstream file(imgPath, std::ios::binary); //open the image file as binary.

    std::string line;
    int hLineCount = 3;

    /* Count number of lines in the header */
    for (int i = 0; i < hLineCount; i++)
    {
        std::getline(file, line);
        if (line[0] == '#') hLineCount++;
    }

    file.seekg(0, file.beg);
    
    /* seek to P */
    do
    {
        file >> line;
        if (line[0] == '#') std::getline(file, line);
    } while (line[0] != 'P');

    /* identify format P */
    if (line[1] != '6')
    {
        std::cout << "ERR : " << imgPath << " is not of format P6! Image not loaded.\n";
        return;
    }

    skipCommentsPPM(file, line);

    /* parse width and height data */
    size[0] = std::stoi(line);
    file >> line;
    size[1] = std::stoi(line);

    /* allocate memory for data according to size */
    mem = new GLubyte[size[0] * size[1] * 3];

    skipCommentsPPM(file, line);

    assert(std::stoi(line) == 255); // we don't like maxval that isn't 255 here.

    /* move pixel data into memory */
    for (int i = 0; i < (size[0] * size[1] * 3); i++)
    {
        char data;
        file.get(data);
        if (data == '\n' && i == 0)
            file.get(data);
        mem[i] = GLubyte(data);
    }
}