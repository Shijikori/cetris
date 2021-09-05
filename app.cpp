#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

// Window Settings
int _G_WIDTH = 640;
int _G_HEIGHT = 480;
int _G_DEPTH = 3;

struct color
{
    float red;
    float green;
    float blue;
    float alpha = 1.0;
    color(float r, float g, float b, float a=1.0)
    {
        red = r;
        green = g;
        blue = b;
        alpha = a;
    }
};

void drawQuad(float x, float y, float size, color color)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glColor4f(color.red, color.green, color.blue, color.alpha);
        glVertex2f(x, y);
        glVertex2f(x + size, y);
        glVertex2f(x + size, y + size);
        glVertex2f(x, y + size);
    glEnd();
}

int main(int argc, char *argv[])
{
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
    //glViewport(GLint(0),GLint(0), _G_WIDTH, _G_HEIGHT);

    // check if window is alive
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // set context
    glfwMakeContextCurrent(window);

    // print GL version
    std::cout << glGetString(GL_VERSION) << "\n";
    
    //gl
    glOrtho(0, _G_WIDTH, 0, _G_HEIGHT, 0, _G_DEPTH);

    // run until window is closed
    while(!glfwWindowShouldClose(window))
    {
        // drawing a quad
        drawQuad(0.0, 0.0, 8, color(0.5, 0.1, 0.7));

        // drawing a triangle
        // TODO : move to function
        /*glBegin(GL_TRIANGLES);
            glColor4f(0.46, 0.1, 0.7, 0.93);
            glVertex2f(0, -0.5);
            glVertex2f(-0.4, 0.5);
            glVertex2f(0.4, 0.5);
        glEnd();*/

        // swap buffers for display (double buffering)
        glfwSwapBuffers(window);

        // poll for events
        glfwPollEvents();
    }

    // terminate GL once window is closed
    glfwTerminate();

    return 0;
}