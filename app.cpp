#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <SFML/Audio.hpp>
#include "libs/shapes.hpp"
#include "libs/image.hpp"

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

    GLubyte *image;
    int image_size[2];
    loadPPM("assets/image/test.ppm", image, image_size);
    std::cout << "imgsize " << image_size[0] << "x" << image_size[1] << std::endl;

    // music settings
    music.setVolume(20.0f);
    music.setLoop(true);
    music.play();

    // run until window is closed
    while(!glfwWindowShouldClose(window))
    {

        // clear buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // draw generated image on screen
        glDrawPixels(fb_w, fb_h, GL_RGB, GL_UNSIGNED_BYTE, bitmap);

        glDrawPixels(image_size[0], image_size[1], GL_RGB, GL_UNSIGNED_BYTE, image);

        // swap buffers for display (double buffering)
        glfwSwapBuffers(window);

        // poll for events
        glfwPollEvents();

    }
    delete[] bitmap;
    delete[] image;
    
    // terminate GL once window is closed
    glfwTerminate();
    return 0;
}