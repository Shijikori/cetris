#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <SFML/Audio.hpp>
#include "libs/shapes.hpp"

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
            mem[pos    ] = 255 - (x % 255);
            mem[pos + 1] = 255 - ((x * y) % 255);
            mem[pos + 2] = y % 255;
        }
    }
    std::cout << "bitmap complete!\n"; // debug
}


int main(int argc, char *argv[])
{
    // Window Settings
    static int _G_WIDTH = 640;  // global width
    static int _G_HEIGHT = 480; // global height
    static int _G_DEPTH = 3;    // global depth

    // declaration of window
    GLFWwindow* window;

    // music
    sf::Music music;
    if (!music.openFromFile("assets/sound/music.ogg"))
        return -1;
    
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

    std::cout << "FB Size w:" << fb_w << " h:" << fb_h << "\n"; // debug output

    genBitmap(fb_w, fb_h, bitmap);


    // music settings
    music.setVolume(50.0);
    music.setLoop(true);
    music.play();

    // run until window is closed
    while(!glfwWindowShouldClose(window))
    {

        // clear buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // draw generated image on screen
        glDrawPixels(fb_w, fb_h, GL_RGB, GL_UNSIGNED_BYTE, bitmap);

        // swap buffers for display (double buffering)
        glfwSwapBuffers(window);

        // poll for events
        glfwPollEvents();

    }
    delete[] bitmap;
    
    // terminate GL once window is closed
    glfwTerminate();
    return 0;
}