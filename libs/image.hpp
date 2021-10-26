#pragma once
#include <GL/gl.h>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cstdint>
#include <iostream>

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
            mem[pos    ] = x * (255.0 / width);
            mem[pos + 1] = 0;
            mem[pos + 2] = y * (255.0 / height);
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

// Generates a 2D texture with an image as an array of GLubytes.
GLuint genTexture2D(GLubyte *&img, int w, int h)
{
    GLuint tex = 0;

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
    return tex;
}

// Makes a texture from a PPM file. Requires path to the file.
GLuint textureFromPPM(std::string path)
{
    GLuint tex = 0;
    GLubyte *image;
    int size[2];

    loadPPM(path, image, size);
    tex = genTexture2D(image, size[0], size[1]);
    
    return tex;

}