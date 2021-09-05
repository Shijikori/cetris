#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <GL/gl.h>
#include <GLFW/glfw3.h>


int main(int argc, char *argv[])
{
    std::cout << "Game starting...\n";
    
    // declaration of window
    GLFWwindow* window;

    // Init Library
    if (!glfwInit()) return -1;

    // Create window
    window = glfwCreateWindow(640, 480, "GLApp", NULL, NULL);

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
    
    // run until window is closed
    while(!glfwWindowShouldClose(window))
    {
        // drawing a quad
        // TODO : move to function
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_QUADS);
            glColor4f(0.5, 0.2, 0.4, 1.0);
            glVertex2f(-0.5, -0.5);
            glVertex2f(0.5, -0.5);
            glVertex2f(0.5, 0.5);
            glVertex2f(-0.5, 0.5);
        glEnd();

        // drawing a triangle
        // TODO : move to function
        glBegin(GL_TRIANGLES);
            glColor4f(0.46, 0.1, 0.7, 0.93);
            glVertex2f(0, -0.5);
            glVertex2f(-0.4, 0.5);
            glVertex2f(0.4, 0.5);
        glEnd();

        // swap buffers for display (double buffering)
        glfwSwapBuffers(window);

        // poll for events
        glfwPollEvents();
    }

    // terminate GL once window is closed
    glfwTerminate();

    return 0;
}