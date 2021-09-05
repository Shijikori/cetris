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
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}