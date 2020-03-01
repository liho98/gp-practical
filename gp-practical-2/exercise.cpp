#include <GL/freeglut.h> // GLUT, include glu.h and gl.h
#include <math.h>

/* Global variables */
char title[] = "Practical 2 exercise", question = '1';
float translateXQ1 = 0.0, translateYQ1 = 0.0, translateXQ3 = 0.0, translateYQ3 = 0.0;
float r = 1.0, g = 1.0, b = 1.0;
float scaleX = 0.0, scaleY = 0.0;
float radius = 1.0, angle = 0.0;
int colorIndex = 0;
float alpha = 0.0;

void init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_POLYGON_SMOOTH);
}

float degToRad(float deg)
{
    return deg * (M_PI / 180);
}

void drawQ1()
{
    glColor3f(r, g, b);
    glTranslatef(translateXQ1, translateYQ1, 0.0);
    glutWireTeapot(0.3);
}

void drawQ2()
{
    // 5 color + 1 repeat
    float r[6] = {33, 104, 244, 255, 76, 33};
    float g[6] = {148, 58, 67, 193, 175, 148};
    float b[6] = {243, 183, 54, 7, 79, 243};

    for (float starAngle = 0.0; starAngle < 360.0; starAngle += 72.0)
    {
        colorIndex = colorIndex % 5;
        glColor4f(1.0, 1.0, 1.0, 0.8);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -7.0f);
        glRotatef(starAngle, 0.0, 0.0, 1.0f);

        glBegin(GL_POLYGON);

        glColor4f(1, 1, 1, alpha);
        glVertex2f(0, 0);

        glColor4ub(r[colorIndex + 1], g[colorIndex + 1], b[colorIndex + 1], alpha);
        glVertex2f(-0.5878, 0.8090); // r cos 54 deg, r sin 54 deg
        
        glColor4ub(r[colorIndex], g[colorIndex], b[colorIndex], alpha);
        glVertex2f(0, 2.0);

        glVertex2f(0.5878, 0.8090); // r cos 54 deg, r sin 54 deg
        glEnd();

        colorIndex++;
    }
}

void drawQ3()
{
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(translateXQ3, translateYQ3, 0.0);
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex2f(0.0, 0.0);
    glEnd();
}

void drawQ4()
{
    glColor3f(1.0, 1.0, 1.0);
    glScalef(scaleX, scaleY, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(-0.01, 0.01);
    glVertex2f(0.01, 0.01);
    glVertex2f(0.01, -0.01);
    glVertex2f(-0.01, -0.01);
    glEnd();
}

void rotate()
{
    if (angle == 360.0)
        angle = 0.0;

    translateXQ3 = cos(degToRad(angle)) * radius;
    translateYQ3 = sin(degToRad(angle)) * radius;
    angle += 1.0;

    glutPostRedisplay();
}

void fade()
{
    alpha = (int) alpha % 255;
    alpha += 5.0;
    glutPostRedisplay();
}

void rotateStarColor(int v)
{
    colorIndex = colorIndex % 5;
    colorIndex++;

    glutPostRedisplay();
    glutTimerFunc(500, rotateStarColor, v);
}

void enlarge()
{
    scaleX += 0.1;
    scaleY += 0.1;
    glutPostRedisplay();
}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display()
{
    // glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT); // Clear color buffers
    glMatrixMode(GL_MODELVIEW);   // To operate on model-view matrix

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -7.0f);

    switch (question)
    {
    case '1':
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -3.0f);
        drawQ1();
        break;
    case '2':
        drawQ2();
        glutIdleFunc(fade);
        break;
    case '3':
        drawQ3();
        glutIdleFunc(rotate);
        // glutTimerFunc(0, rotate, 0);
        break;
    case '4':
        drawQ4();
        glutIdleFunc(enlarge);
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
        translateXQ1 -= 0.1;
        break;
    case GLUT_KEY_RIGHT:
        translateXQ1 += 0.1;
        break;
    case GLUT_KEY_UP:
        translateYQ1 += 0.1;
        break;
    case GLUT_KEY_DOWN:
        translateYQ1 -= 0.1;
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
    case 'r':
        r = 1.0;
        g = 0.0;
        b = 0.0;
        break;
    case 'g':
        r = 0.0;
        g = 1.0;
        b = 0.0;
        break;
    case 'b':
        r = 0.0;
        g = 0.0;
        b = 1.0;
        break;
    case 32:
        r = 1.0;
        g = 1.0;
        b = 1.0;
        translateXQ1 = 0.0;
        translateYQ1 = 0.0;
        break;
    case '1':
        question = '1';
        break;
    case '2':
        question = '2';
        break;
    case '3':
        question = '3';
        break;
    case '4':
        question = '4';
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
    glutSetOption(GLUT_MULTISAMPLE, 16);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE); // Enable double buffered mode
    glutInitWindowSize(800, 800);                                                 // Set the window's initial width & height
    glutInitWindowPosition(0, 0);                                                 // Position the window's initial top-left corner
    glutCreateWindow(title);                                                      // Create window with the given title

    init();

    glutDisplayFunc(display); // Register callback handler for window re-paint event
    glutReshapeFunc(reshape); // Register callback handler for window re-size event
    glutSpecialFunc(SpecialKeyHandler);
    glutKeyboardFunc(NormalKeyHandler);
    glutTimerFunc(0, rotateStarColor, 0);
    glutMainLoop(); // Enter the infinite event-processing loop
    return 0;
}