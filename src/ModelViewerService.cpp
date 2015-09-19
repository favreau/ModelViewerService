/*
 *
 * Demonstrates how to load and display an Wavefront OBJ file.
 * Using triangles and normals as static object. No texture mapping.
 * https://tutorialsplay.com/opengl/
 *
 * OBJ files must be triangulated!!!
 * Non triangulated objects wont work!
 * You can use Blender to triangulate
 *
 */

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#ifdef __APPLE__
#  include "GLUT/glut.h"
#else
#  include "GL/glut.h"
#endif
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include "ModelLoader.h"

#define KEY_ESCAPE 27

using namespace std;

/************************************************************************
  Window
 ************************************************************************/

typedef struct {
    int width;
    int height;
    std::string title;

    float field_of_view_angle;
    float z_near;
    float z_far;
} glutWindow;

#define POINTS_PER_VERTEX 3
#define TOTAL_FLOATS_IN_TRIANGLE 9
using namespace std;

/***************************************************************************
 * Program code
 ***************************************************************************/

ModelLoader obj;
float g_rotation = 0.f;
glutWindow win;

void display() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt( 0,0,30, 0,0,0, 0,1,0);
    glPushMatrix();
    glRotatef(g_rotation,0,1,0);
    g_rotation += 0.5f;
    obj.draw();
    glPopMatrix();
    glutSwapBuffers();
}

void initialize () 
{
    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, win.width, win.height);
    GLfloat aspect = (GLfloat) win.width / win.height;
    glLoadIdentity();
    gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);

    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);               // Set background color to black and opaque

    glDepthMask(GL_TRUE);
    glClearDepth(1.0f);                                 // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);                            // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);                             // Set the type of depth-test
    glShadeModel(GL_SMOOTH);                            // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
    GLfloat specular[] = { 0.7, 0.7, 0.3, 1 };
    glLightfv( GL_FRONT, GL_DIFFUSE, diffuse );
    glLightfv( GL_FRONT, GL_SPECULAR, specular );
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
}

void keyboard ( unsigned char key, int, int )
{
    switch ( key ) {
    case KEY_ESCAPE:
        exit ( 0 );
        break;
    default:
        break;
    }
}

int main(int argc, char **argv)
{
    // set window values
    win.width = 640;
    win.height = 480;
    win.title = "OBJ Viewer Service";
    win.field_of_view_angle = 45;
    win.z_near = 1.0f;
    win.z_far = 500.0f;

    // initialize and run program
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH );
    glutInitWindowSize(win.width,win.height);
    glutCreateWindow(win.title.c_str());
    glutDisplayFunc(display);
    glutIdleFunc( display );
    glutKeyboardFunc( keyboard );
    initialize();
    obj.loadFromFile("../models", "neuron.obj");
    glutMainLoop();
    return 0;
}
