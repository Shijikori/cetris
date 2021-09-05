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

    if (dpy == NULL)
    {
        std::cout << "Could not connect to X server\n\n";
        exit(0);
    }

    root = DefaultRootWindow(dpy);

    vi = glXChooseVisual(dpy, 0, att);

    if (vi == NULL)
    {
        std::cout << "Could not find appropriate visuals\n\n";
        exit(0);
    }
    else
    {
        std::printf("\n\tvisual %p selected\n", (void *)vi->visualid);
    }

    cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);

    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask;

    win = XCreateWindow(dpy, root, 0, 0, 600, 600, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);

    XMapWindow(dpy, win);
    XStoreName(dpy, win, "GLApp");

    glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
    glXMakeCurrent(dpy, win, glc);

    glEnable(GL_DEPTH_TEST);

    while(1)
    {
        XNextEvent(dpy, &xev);

        if (xev.type == Expose)
        {
            XGetWindowAttributes(dpy, win, &gwa);
            glViewport(0, 0, gwa.width, gwa.height);
            drawQuad();
            glXSwapBuffers(dpy, win);
        }
        else if (xev.type == KeyPress)
        {
            glXMakeCurrent(dpy, None, NULL);
            glXDestroyContext(dpy, glc);
            XDestroyWindow(dpy, win);
            XCloseDisplay(dpy);
            exit(0);
        }
    }
    
    return 0;
}