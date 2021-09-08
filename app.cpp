#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "libs/shapes.hpp"



int main(int argc, char *argv[])
{
    // Window Settings
    static int _G_WIDTH = 640;
    static int _G_HEIGHT = 480;
    static int _G_DEPTH = 3;

    std::cout << "Game starting...\n";
    
    // declaration of window
    GLFWwindow* window;

    // Init Library
    if (!glfwInit()) return -1;

    // Create window
    window = glfwCreateWindow(_G_WIDTH, _G_HEIGHT, "GLApp", NULL, NULL);

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

    // initial coordinates for square
    int x = 0;
    int y = 200;
    // run until window is closed
    while(!glfwWindowShouldClose(window))
    {
        // calculate size from quadratic fonction
        float size = ((-0.00087890625 * pow(x, 2)) + (0.5625*x));

        // drawing a quad
        drawSquare(x, y, size, color(0.5, 0.1, 0.7));

        // swap buffers for display (double buffering)
        glfwSwapBuffers(window);

        // poll for events
        glfwPollEvents();
        if (x > _G_WIDTH) x = 0;
        x++;
    }

    // terminate GL once window is closed
    glfwTerminate();

    return 0;
}