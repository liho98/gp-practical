#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// Mode
int currentMode = 0;
bool toggleLighting = true;

// Screen
const float screenWidth = 800, screenHeight = 600;

// Camera
float orthoLeft = -5.0f, orthoRight = 5.0f, orthoBottom = -5.0f, orthoTop = 5.0f, orthoZNear = 0, orthoZFar = 10.0f;
float prespFovy = 60;
float prespLeft = -1.0f, prespRight = 1.0f, prespBottom = -1.0f, prespTop = 1.0f, prespZNear = 0, prespZFar = 10.0f;
float lastCursorPosX, lastCursorPosY;
float cameraPosX = 0, cameraPosY = 0, cameraPosZ = 0, cameraRotX = 0, cameraRotY = 0;
POINT cursorPos;

// Lighting
float lightPos[] = { 0, 1, 0 };
float lightMovementSpd = 0.1f;
float lightDif[] = { 1, 1, 1 };

// Model
int currentModel = 0;
float modelColor[] = { 0.52f, 0.52f, 0.52f };
float rotDeg = 0.0, rotSpd = 1;

void init()
{
    glEnable(GL_DEPTH_TEST); // Enable depth testing for z-culling

}

void display()
{

    glPushMatrix();
    {
        if (rotate)
        {
            glRotatef(rotateObj, 1, 1, 1);
        }
        else
        {
            glRotatef(0, 1, 1, 1);
        }

        drawCube(1.0);

        // if (pyramid)
        // {
        //     drawPyramid(0.6);
        // }
        // else
        // {
        //     drawCube(0.6);
        // }
    }
    glPopMatrix();
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
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practical 7", NULL, NULL);
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
        rotateObj = sin(glfwGetTime()) * 90.0;
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
    glDisable(GL_TEXTURE_2D);
    glDeleteTextures(1, &textures[0]);
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
            rotate = !rotate;
        default:
            break;
        }
    }
}

void processInput(GLFWwindow *window)
{
    // if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
    //     pyramid = false;
    // if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    //     pyramid = true;
    // if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    //     rotateClockwise = true;
    // if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    //     rotateClockwise = false;
    // if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    //     diffusePosition[1] += 0.01;
    // if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    //     diffusePosition[1] -= 0.01;
    // if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    //     diffusePosition[0] -= 0.01;
    // if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    //     diffusePosition[0] += 0.01;
    // if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    //     diffusePosition[2] += 0.01;
    // if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    //     diffusePosition[2] -= 0.01;
}