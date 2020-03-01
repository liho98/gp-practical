#include <GL/freeglut.h> // GLUT, include glu.h and gl.h
#include <math.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

/* Global variables */
char title[] = "Practical 2 exercise", question = '1';
float translateX = 0.0, translateY = 0.0;
float rAngle = 0.0, speed = 0.0f;
unsigned ms = 1000;
float noOfPropeller = 120.0;
int background = 0;

GLuint texture;
GLuint *textures = new GLuint[2];
int width, height, nrChannels;

float degToRad(float deg)
{
    return deg * (M_PI / 180);
}

void rotate(int v)
{
    rAngle -= speed;

    glutPostRedisplay();
    glutTimerFunc(ms, rotate, v);
}

/*  Initialize alpha blending function.  */
void init(void)
{
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_MULTISAMPLE);
    glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
    GLint bufs, samples;
    glGetIntegerv(GL_SAMPLE_BUFFERS, &bufs);
    glGetIntegerv(GL_SAMPLES, &samples);
    printf("MSAA on, GL_SAMPLE_BUFFERS = %d, GL_SAMPLES = %d\n", bufs, samples);

    // glEnable (GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);

    // glHint (GL_POINT_SMOOTH, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    glPointSize(10);

    glGenTextures(2, textures);

    glEnable(GL_TEXTURE_2D);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    // load and generate the texture
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("/home/liho/Desktop/graphic-programming/gp-practical-3/bg.jpg", &width, &height, &nrChannels, 0);

    if (data)
    {
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    data = stbi_load("/home/liho/Desktop/graphic-programming/gp-practical-3/1.jpg", &width, &height, &nrChannels, 0);

    if (data)
    {
        glBindTexture(GL_TEXTURE_2D, textures[1]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void drawQ1()
{
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-translateX, translateY, -2.0f);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(-0.25, 0.15);
    glVertex2f(0.25, 0.15);
    glVertex2f(0.25, -0.15);
    glVertex2f(-0.25, -0.15);
    glEnd();
    glPopMatrix();

    glTranslatef(translateX, -translateY, -2.0f);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(-0.25, 0.15);
    glVertex2f(0.25, 0.15);
    glVertex2f(0.25, -0.15);
    glVertex2f(-0.25, -0.15);
    glEnd();
}

void drawQ2()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-1.0f, 0.0f, -2.0f);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 1.0, 1.0);
    for (float angle = degToRad(0); angle < degToRad(360); angle += 0.01)
    {
        glVertex2f(cos(angle) * 0.02, sin(angle) * 0.3);
    }
    glEnd();

    glLoadIdentity();
    glTranslatef(-1.0f, -0.2f, -2.0f);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(-0.02, 0.15);
    glVertex2f(0.02, 0.15);
    glVertex2f(0.03, -0.5);
    glVertex2f(-0.03, -0.5);
    glEnd();

    glLoadIdentity();
    glTranslatef(-1.0f, 0.3f, -2.0f);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 1.0, 1.0);
    for (float angle = degToRad(0); angle < degToRad(360); angle += 0.01)
    {
        glVertex2f(cos(angle) * 0.025, sin(angle) * 0.025);
    }
    glEnd();

    for (float i = 0; i <= 360; i = i + noOfPropeller)
    {
        glLoadIdentity();
        glTranslatef(-1.0f, 0.3f, -2.0f);

        glRotatef(rAngle, 0.0f, 0.0f, 1.0f);

        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_QUADS);
        glVertex2f(0.0, 0.4);
        glVertex2f(0.01, 0.0);
        glVertex2f(-0.01, 0.0);
        glVertex2f(-0.025, 0.2);
        glEnd();

        rAngle += noOfPropeller;
    }
}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display()
{
    // glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT); // Clear color buffers

    // // background texture
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glBindTexture(GL_TEXTURE_2D, textures[background]);
    glBegin(GL_QUADS);
    glColor3f(255.0 / 255, 255.0 / 255, 255.0 / 255);

    glTexCoord2f(0, 0);
    glVertex2f(-1, -1);
    glTexCoord2f(1, 0);
    glVertex2f(1, -1);
    glTexCoord2f(1, 1);
    glVertex2f(1, 1);
    glTexCoord2f(0, 1);
    glVertex2f(-1, 1);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    switch (question)
    {
    case '1':
        drawQ1();
        break;
    case '2':
        drawQ2();
        break;
    default:
        break;
    }

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
        glutFullScreenToggle();
        break;
    case GLUT_KEY_LEFT:
        translateX -= 0.1;
        break;
    case GLUT_KEY_RIGHT:
        translateX -= 0.1;
        break;
    case GLUT_KEY_UP:
        translateY -= 0.1;
        break;
    case GLUT_KEY_DOWN:
        translateY -= 0.1;
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
    case 32:
        translateX = 0.0;
        translateY = 0.0;

        if (ms == 1000)
        {
            speed = 10.0;
            ms = 90;
        }
        else
        {
            ms = 1000;
            speed = 0;
        }
        break;
    case '1':
        question = '1';
        break;
    case '2':
        question = '2';
        break;
    case 'a':
        if (ms > 10)
            ms -= 10;
        break;
    case 's':
        if (ms < 100)
            ms += 10;
        break;
    case 'd':
        speed = -speed;
        break;
    case 'f':
        noOfPropeller = 360 / ((360.0 / noOfPropeller) + 1);
        glutPostRedisplay();
        break;
    case 'g':
        if (floor(360.0 / noOfPropeller) > 3.0)
        {
            noOfPropeller = 360 / ((360.0 / noOfPropeller) - 1);
            glutPostRedisplay();
        }
        break;
    case '0':
        if (background == 0)
            background = 1;
        else
            background = 0;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char **argv)
{
    glutInit(&argc, argv); // Initialize GLUT
    glutSetOption(GLUT_MULTISAMPLE, 4);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE); // Enable double buffered mode
    glutInitWindowSize(1920, 1080);                                               // Set the window's initial width & height
    glutInitWindowPosition(0, 0);                                                 // Position the window's initial top-left corner
    glutCreateWindow(title);                                                      // Create window with the given title

    init();

    glutReshapeFunc(reshape); // Register callback handler for window re-size event
    glutDisplayFunc(display); // Register callback handler for window re-paint event
    glutSpecialFunc(SpecialKeyHandler);
    glutKeyboardFunc(NormalKeyHandler);
    glutTimerFunc(0, rotate, 0);

    glutMainLoop(); // Enter the infinite event-processing loop
    return 0;
}