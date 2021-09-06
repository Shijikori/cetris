#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

// Window Settings
int _G_WIDTH = 640;
int _G_HEIGHT = 480;
int _G_DEPTH = 3;

// Color struct to store color data
struct color
{
    float red;
    float green;
    float blue;
    float alpha = 1.0;
    // constructor
    color(float r, float g, float b, float a=1.0)
    {
        red = r;
        green = g;
        blue = b;
        alpha = a;
    }
};

// Draw a quad
void drawQuad(float x, float y, float w, float h, color color)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glColor4f(color.red, color.green, color.blue, color.alpha);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
    glEnd();
}

// Draw a square
void drawSquare(float x, float y, float size, color color)
{
    drawQuad(x,y,size,size,color);
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
    
    // set resolution scale
    glOrtho(0, _G_WIDTH, 0, _G_HEIGHT, 0, _G_DEPTH);

    // run until window is closed
    int x = 0;
    int y = 200;
    while(!glfwWindowShouldClose(window))
    {
        // calculate size from quadratic fonction
        float size = ((-0.00087890625 * pow(x, 2)) + (0.5625*x));
        std::cout << size << std::endl;

        // drawing a quad
        drawSquare(x, y, size, color(0.5, 0.1, 0.7));

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
        if (x > _G_WIDTH) x = 0;
        //if (y > _G_HEIGHT) y = 0;
        x++;
    }

    // terminate GL once window is closed
    glfwTerminate();

    return 0;
}