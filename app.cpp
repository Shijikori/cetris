#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SFML/Audio.hpp>
#include "libs/shapes.hpp"
#include "libs/image.hpp"

int main(int argc, char *argv[])
{
    // Window Settings
    static int _G_WIDTH = 640;  // global width
    static int _G_HEIGHT = 480; // global height
    static int _G_DEPTH = 3;    // global depth - actually useless, leaving it for now.

    // declaration of window
    GLFWwindow* window;

    // music
    sf::Music music;
    if (!music.openFromFile("assets/sound/music.ogg"))
        return -1;
    
    // Init Library
    if (!glfwInit()) return -1;

    // Set window attributes
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create window
    window = glfwCreateWindow(_G_WIDTH, _G_HEIGHT, "Cetris [Indev]", NULL, NULL);

    // check if window is alive
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // set context
    glfwMakeContextCurrent(window);

    // load extensions
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err)
    {
        std::cout << "Failed to load GL Extensions.\n" << glewGetErrorString(err) << "\n";
        return -1;
    }

    // print GL version
    std::cout << glGetString(GL_RENDERER) << "\n";
    std::cout << glGetString(GL_VERSION) << "\n";
    
    glViewport(0, 0, _G_WIDTH, _G_HEIGHT);

    // set GL orthographic view
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, _G_WIDTH, 0, _G_HEIGHT, 0, _G_DEPTH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Generating a bitmap for glDrawPixels
    GLubyte *bitmap;   // bitmap pointer
    int fb_w, fb_h; // framebuffer width and height variables
    
    glfwGetFramebufferSize(window, &fb_w, &fb_h); //get FB size to make proper image

    std::cout << "FB Size w:" << fb_w << " h:" << fb_h << "\n"; // debug output

    glEnable(GL_TEXTURE_2D); // Make sure 2D textures are enabled *shrug*

    GLuint tex[2];
    tex[0] = textureFromPPM("assets/textures/brick-background.ppm");
    genBitmap(fb_w, fb_h, bitmap);
    tex[1] = genTexture2D(bitmap, fb_w, fb_h);

    // music settings
    music.setVolume(20.0f);
    music.setLoop(true);
    music.play();

    // run until window is closed
    while(!glfwWindowShouldClose(window))
    {

        // clear buffer
        glClear(GL_COLOR_BUFFER_BIT);

        drawQuad(0, 0, fb_w, fb_h, tex[1]);

        //drawQuad((fb_w / 2) - 32, (fb_h / 2) - 32, 64, 64, tex[0]);
        drawQuadRepeatTex(0, 0, fb_w, fb_h, tex[0], 128, 128);

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