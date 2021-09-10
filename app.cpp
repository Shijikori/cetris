#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "libs/shapes.hpp"

void genBitmap(int width, int height, GLubyte *&mem)
{
    //glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_INT_8_8_8_8, map); (targert format)

    if (!mem) std::free(mem);
    mem = new GLubyte[width * height * 3];
    
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int pos = (x + y * width) * 3;
            mem[pos    ] = 255 - (x % 255);
            mem[pos + 1] = 255 - ((x * y) % 255);
            mem[pos + 2] = y % 255;
        }
    }
    std::cout << "bitmap complete!\n";
}

// Pixel struct, might be unused
struct pixel
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t padding;
    // construtor
    pixel(uint8_t r, uint8_t g, uint8_t b)
    {
        red = r;
        green = g;
        blue = b;
        padding = 0;
    }
};

int main(int argc, char *argv[])
{
    // Window Settings
    static int _G_WIDTH = 640;  // global width
    static int _G_HEIGHT = 480; // global height
    static int _G_DEPTH = 3;    // global depth

    std::cout << "Game starting...\n";
    
    // declaration of window
    GLFWwindow* window;

    // Init Library
    if (!glfwInit()) return -1;

    // Create window
    window = glfwCreateWindow(_G_WIDTH, _G_HEIGHT, "Cetris [Indev]", NULL, NULL);

    // Set window attributes
    glfwSetWindowMonitor(window, NULL, 0, 0, 0, 0, 60); // 60fps cap *hypothetical
    glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE); // makes window unresizable

    // check if window is alive
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // set context
    glfwMakeContextCurrent(window);

    // print GL version
    std::cout << glGetString(GL_RENDERER) << "\n";
    std::cout << glGetString(GL_VERSION) << "\n";
    
    // set resolution scale
    glOrtho(0, _G_WIDTH, 0, _G_HEIGHT, 0, _G_DEPTH);

    // Generating a bitmap for glDrawPixels
    GLubyte *bitmap;   // bitmap pointer
    int fb_w, fb_h; // framebuffer width and height variables
    
    glfwGetFramebufferSize(window, &fb_w, &fb_h); //get FB size to make proper image

    std::cout << "FB Size w:" << fb_w << " h:" << fb_h << "\n";
    std::cout << "f:" << bitmap << "f&:" << &bitmap << "\n";
    genBitmap(fb_w, fb_h, bitmap);
    //genBitmap(fb_w, fb_h, bitmap);

    // run until window is closed
    while(!glfwWindowShouldClose(window))
    {

        // clear buffer
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawPixels(fb_w, fb_h, GL_RGB, GL_UNSIGNED_BYTE, bitmap);

        // swap buffers for display (double buffering)
        glfwSwapBuffers(window);

        // poll for events
        glfwPollEvents();

    }
    std::free(bitmap);
    // terminate GL once window is closed
    glfwTerminate();
    return 0;
}