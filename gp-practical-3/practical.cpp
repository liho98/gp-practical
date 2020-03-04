// #include <GL/freeglut.h> // GLUT, include glu.h and gl.h
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <math.h>
#include <iostream>
/* Global variables */
char title[] = "Practical 3 exercise";

/*  Initialize alpha blending function.  */
void init(void)
{
    // glEnable(GL_BLEND);
    // glDisable(GL_DEPTH_TEST);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // glEnable(GL_MULTISAMPLE);
    // glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
    // GLint bufs, samples;
    // glGetIntegerv(GL_SAMPLE_BUFFERS, &bufs);
    // glGetIntegerv(GL_SAMPLES, &samples);
    // printf("MSAA on, GL_SAMPLE_BUFFERS = %d, GL_SAMPLES = %d\n", bufs, samples);

    // // glEnable (GL_POINT_SMOOTH);
    // glEnable(GL_LINE_SMOOTH);
    // glEnable(GL_POLYGON_SMOOTH);

    // // glHint (GL_POINT_SMOOTH, GL_NICEST);
    // glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    // glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    // glPointSize(10);
}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display()
{
    // glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT); // Clear color buffers

	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0.5, 0.0, 0.0);
	glScalef(0.5, 0.5, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.5, 0.0);
	glVertex2f(0.0, 0.5);
	glVertex2f(0.5, 0.0);
	glEnd();
	glPopMatrix();

	glTranslatef(-0.5, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(-0.5, 0.0);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, 0.0);
	glEnd();


    glutSwapBuffers(); // Swap the front and back frame buffers (double buffering)
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height)
{ // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0)
        height = 1; // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
    glLoadIdentity();            // Reset
    // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void SpecialKeyHandler(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_F12: /*  Escape key  */
        glutFullScreen();
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

void NormalKeyHandler(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: /*  Escape key  */
        exit(0);
        break;
    default:
        break;
    }
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char **argv)
{
    glutInit(&argc, argv); // Initialize GLUT
    // glutSetOption(GLUT_MULTISAMPLE, 16);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE); // Enable double buffered mode
    glutInitWindowSize(1920, 1080);                                               // Set the window's initial width & height
    glutInitWindowPosition(0, 0);                                                 // Position the window's initial top-left corner
    glutCreateWindow(title);                                                      // Create window with the given title

    init();

    glutDisplayFunc(display); // Register callback handler for window re-paint event
    // glutReshapeFunc(reshape); // Register callback handler for window re-size event
    glutSpecialFunc(SpecialKeyHandler);
    glutKeyboardFunc(NormalKeyHandler);

    glutMainLoop(); // Enter the infinite event-processing loop
    return 0;
}