#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <GL/gl.h>
#include <GLFW/glfw3.h>


int main(int argc, char *argv[])
{
    std::cout << "Game starting...\n";
    
    GLFWwindow* window;

    // Init Library
    if (!glfwInit()) return -1;

    // Create window
    window = glfwCreateWindow(640, 480, "GLApp", NULL, NULL);
    glfwSetWindowMonitor(window, NULL, 0, 0, 0, 0, 60);
    glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_QUADS);
            glColor4f(0.5, 0.2, 0.4, 1.0);
            glVertex2f(-0.5, -0.5);
            glVertex2f(0.5, -0.5);
            glVertex2f(0.5, 0.5);
            glVertex2f(-0.5, 0.5);
        glEnd();

        glBegin(GL_TRIANGLES);
            glColor4f(0.46, 0.1, 0.7, 0.93);
            glVertex2f(0, -0.5);
            glVertex2f(-0.4, 0.5);
            glVertex2f(0.4, 0.5);
        glEnd();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}