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
float z = 0.0, speed = 0.1;

void init()
{
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
    gluPerspective(45.0f, 1.0, -1.0, 1.0);
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
}

void display()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, z);
    var = gluNewQuadric();
    gluSphere(var, 0.5, 30, 30);
    gluDeleteQuadric(var);
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
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // configure global opengl state
    // -----------------------------

    init();
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        // render
        // ------
        // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // glMatrixMode(GL_MODELVIEW); // To operate on model-view matrix

        // glLoadIdentity();
        display();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// // glfw: whenever the window size changed (by OS or user resize) this callback function executes
// // ---------------------------------------------------------------------------------------------
// void framebuffer_size_callback(GLFWwindow *window, int width, int height)
// {
//     if (height == 0)
//         height = 1; // To prevent divide by 0
//     GLfloat aspect = (GLfloat)width / (GLfloat)height;

//     // Set the viewport to cover the new window
//     glViewport(0, 0, width, height);

//     // Set the aspect ratio of the clipping volume to match the viewport
//     glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
//     glLoadIdentity();            // Reset
//     // Enable perspective projection with fovy, aspect, zNear and zFar

//     gluPerspective(45.0f, aspect, 0.1f, 100.0f);
// }

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        z += speed;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        z -= speed;
}