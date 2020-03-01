#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

bool rotateClockwise = true;
bool pyramid = false;
bool light = true;
float rotateObj = 0.0;

float diffuseColor[] = {1.0f, 0.0f, 0.0f};
float diffusePosition[] = {0.0f, 1.0f, 0.0f};
float objectColor[] = {1.0f, 1.0f, 1.0f};

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

void init()
{
    glEnable(GL_DEPTH_TEST); // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Nice perspective corrections

    glPointSize(7.0);
}

void drawPyramid(float size)
{
    glBegin(GL_QUADS);

    // Bottom face
    // glColor3f(1.0f, 0.5f, 0.0f); // Orange
    glNormal3f(0, -1, 0);
    glVertex3f(size, -size, size);
    glVertex3f(-size, -size, size);
    glVertex3f(-size, -size, -size);
    glVertex3f(size, -size, -size);
    glEnd();

    glBegin(GL_TRIANGLES);
    // Left face
    // glColor3f(0.0f, 0.0f, 1.0f); // Blue
    glNormal3f(-1, 0, 0);
    glVertex3f(0.0f, size, 0.0f);
    glVertex3f(-size, -size, -size);
    glVertex3f(-size, -size, size);

    // Back face
    // glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    glNormal3f(0, 0, -1);
    glVertex3f(0.0f, size, 0.0f);
    glVertex3f(-size, -size, -size);
    glVertex3f(size, -size, -size);

    // Right face
    // glColor3f(1.0f, 0.0f, 1.0f); // Magenta
    glNormal3f(1, 0, 0);
    glVertex3f(0.0f, size, 0.0f);
    glVertex3f(size, -size, size);
    glVertex3f(size, -size, -size);

    // Front face
    // glColor3f(1.0f, 0.0f, 0.0f); // Red
    glNormal3f(0, 0, 1);
    glVertex3f(0.0f, size, 0.0f);
    glVertex3f(size, -size, size);
    glVertex3f(-size, -size, size);

    glEnd();
}

void drawSphere()
{
    GLUquadricObj *sphere = NULL;
    sphere = gluNewQuadric();
    // glMaterialfv(GL_FRONT, GL_AMBIENT, objectColor);
    glLineWidth(4);
    glColor3f(0, 0, 0);
    gluQuadricDrawStyle(sphere, GLU_POINT);
    gluSphere(sphere, 0.8, 50, 50);
    gluDeleteQuadric(sphere);
}

void display()
{
    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();

    // glTranslatef(0, 0, -7.0);
    // glRotatef(-rotateCam, 0.0, 1.0, 0.0);

    if (light)
    {
        glPushMatrix();
        {
            glLoadIdentity();
            glEnable(GL_LIGHTING);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);
            glLightfv(GL_LIGHT0, GL_POSITION, diffusePosition);
            glEnable(GL_LIGHT0);
        }
        glPopMatrix();
    }
    glPushMatrix();
    {
        if (rotateClockwise)
        {
            glRotatef(-rotateObj, 1, 1, 1);
        }
        else
        {
            glRotatef(rotateObj, 1, 1, 1);
        }

        if (pyramid)
        {
            drawPyramid(0.6);
        }
        else
        {
            drawSphere();
        }
    }
    glPopMatrix();
    glPushMatrix();
    {
        // glLoadIdentity();
        // glMaterialfv(GL_FRONT, GL_AMBIENT, objectColor);
        // glColor3f(1.0f, 0, 0);
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);

        GLUquadricObj *sphere = NULL;
        sphere = gluNewQuadric();
        glTranslatef(diffusePosition[0], diffusePosition[1], diffusePosition[2]);
        // glPointSize(2);
        if (light)
            glColor3f(1.0f, 0, 0);
        else
            glColor3f(0, 0, 0);

        gluQuadricDrawStyle(sphere, GLU_FILL);
        gluSphere(sphere, 0.1, 50, 50);
        gluDeleteQuadric(sphere);
    }
    glPopMatrix();

    // glEnable(GL_LIGHTING);
    // glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    // glLightfv(GL_LIGHT0, GL_POSITION, pos);
    // glEnable(GL_LIGHT0);

    // glLightfv(GL_LIGHT1, GL_DIFFUSE, dif);
    // glLightfv(GL_LIGHT1, GL_POSITION, pos1);
    // glEnable(GL_LIGHT1);

    // glColor3f(1, 0, 0);
    // GLUquadric * sphere = NULL;
    // sphere = gluNewQuadric();
    // gluSphere(sphere, 0.5, 30, 30);
    // gluDeleteQuadric(sphere);
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practical 6", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // configure global opengl state
    // -----------------------------
    init();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        rotateObj = glfwGetTime() * 20.0;
        // render
        // ------
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW); // To operate on model-view matrix

        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -7.0f);
        display();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
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

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{

    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, true);
            break;
        case GLFW_KEY_SPACE:
            light = !light;
        default:
            break;
        }
    }
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        pyramid = false;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        pyramid = true;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        rotateClockwise = true;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        rotateClockwise = false;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        diffusePosition[1] += 0.01;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        diffusePosition[1] -= 0.01;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        diffusePosition[0] -= 0.01;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        diffusePosition[0] += 0.01;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        diffusePosition[2] += 0.01;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        diffusePosition[2] -= 0.01;
}