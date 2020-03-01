#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

GLUquadricObj *var = NULL;
double rotateCam = 0, rotateBi = 0, rotateBii = 0;

float amb[] = { 1,0,0 };
float pos[] = { 0,1,0 };
float dif[] = { 0,1,0 };
float pos1[] = { 1,0,0 };

void init()
{
    glClearDepth(1.0f);                                // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);                           // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);                            // Set the type of depth-test
    glShadeModel(GL_SMOOTH);                           // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Nice perspective corrections

    glPointSize(10.0);
}

void display()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0, 0, -7.0);
    glRotatef(-rotateCam, 0.0, 1.0, 0.0);

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT1, GL_POSITION, pos1);
	glEnable(GL_LIGHT1);

	glColor3f(1, 0, 0);
	GLUquadric * sphere = NULL;
	sphere = gluNewQuadric();
	gluSphere(sphere, 0.5, 30, 30);
	gluDeleteQuadric(sphere);
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
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    init();
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        // rotateCam = glfwGetTime() * 90.0;
        // render
        // ------
        // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        rotateCam += 1;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        rotateCam -= 1;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        rotateBi += 20;
        rotateBii -= 20;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        rotateBi -= 20;
        rotateBii += 20;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        rotateCam = 0;
        rotateBi = 0;
        rotateBii = 0;
    }
}