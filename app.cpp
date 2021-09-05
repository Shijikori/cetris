#include <cstdio>
#include <cstdlib>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <iostream>

Display *dpy;
Window root;
GLint att[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};
XVisualInfo *vi;
Colormap cmap;
XSetWindowAttributes swa;
Window win;
GLXContext glc;
XWindowAttributes gwa;
XEvent xev;

void drawQuad()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.,1.,-1.,1.,1.,20.);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.,0.,10.,0.,0.,0.,0.,1.,0.);

    glBegin(GL_QUADS);
        glColor3f(1.,0.,0.); glVertex3f(-.75,-.75,0.);
        glColor3f(1.,0.,0.); glVertex3f(.75,-.75,0.);
        glColor3f(1.,0.,0.); glVertex3f(.75,.75,0.);
        glColor3f(1.,0.,0.); glVertex3f(-.75,.75,0.);
    glEnd();
}

int main(int argc, char *argv[])
{
    std::cout << "Game starting...\n";
    

    dpy = XOpenDisplay(NULL);

    root = DefaultRootWindow(dpy);

    vi = glXChooseVisual(dpy, 0, att);

    if (vi == NULL)
    {
        std::cout << "Could not find appropriate visuals\n\n";
        exit(0);
    }
    if (dpy == NULL)
    {
        std::cout << "Could not connect to X server\n\n";
        exit(0);
    }
    return 0;
}