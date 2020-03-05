#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

GLuint LoadTexture(const char *fileName);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

GLuint *textures = new GLuint[1];
int width, height, nrChannels;

bool rotate = true;
float rotateObj = 0.0;

void init()
{
    glEnable(GL_DEPTH_TEST); // Enable depth testing for z-culling
    // glDepthFunc(GL_LEQUAL);
    // glDisable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    // glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Nice perspective corrections

    glEnable(GL_TEXTURE_2D);
    LoadTexture("/home/liho/Desktop/graphic-programming/gp-practical-7/Box.bmp");
}

GLuint LoadTexture(const char *fileName)
{
    // set the texture wrapping/filtering options (on the currently bound texture object)
    // load and generate the texture
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(fileName, &width, &height, &nrChannels, 3);

    if (data)
    {
        glGenTextures(1, &textures[0]);
        glBindTexture(GL_TEXTURE_2D, textures[0]);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        // glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // default

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBindTexture(textures[0], 0);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
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

void drawCube(float size)
{
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    
    glBegin(GL_QUADS); // Begin drawing the color cube with 6 quads
    // Top face (y = 1.0f)
    // Define vertices in counter-clockwise (CCW) order with normal pointing out
    glTexCoord2f(0, 0);
    glVertex3f(size, size, -size);
    glTexCoord2f(1, 0);
    glVertex3f(-size, size, -size);
    glTexCoord2f(1, 1);
    glVertex3f(-size, size, size);
    glTexCoord2f(0, 1);
    glVertex3f(size, size, size);

    // Bottom face (y = -1.0f)
    glTexCoord2f(0, 0);
    glVertex3f(size, -size, size);
    glTexCoord2f(1, 0);
    glVertex3f(-size, -size, size);
    glTexCoord2f(1, 1);
    glVertex3f(-size, -size, -size);
    glTexCoord2f(0, 1);
    glVertex3f(size, -size, -size);

    // Front face  (z = 1.0f)
    glTexCoord2f(0, 0);
    glVertex3f(size, size, size);
    glTexCoord2f(1, 0);
    glVertex3f(-size, size, size);
    glTexCoord2f(1, 1);
    glVertex3f(-size, -size, size);
    glTexCoord2f(0, 1);
    glVertex3f(size, -size, size);

    // Back face (z = -1.0f)
    glTexCoord2f(0, 0);
    glVertex3f(size, -size, -size);
    glTexCoord2f(1, 0);
    glVertex3f(-size, -size, -size);
    glTexCoord2f(1, 1);
    glVertex3f(-size, size, -size);
    glTexCoord2f(0, 1);
    glVertex3f(size, size, -size);

    // Left face (x = -1.0f)
    glTexCoord2f(0, 0);
    glVertex3f(-size, size, size);
    glTexCoord2f(1, 0);
    glVertex3f(-size, size, -size);
    glTexCoord2f(1, 1);
    glVertex3f(-size, -size, -size);
    glTexCoord2f(0, 1);
    glVertex3f(-size, -size, size);

    // Right face (x = 1.0f)
    glTexCoord2f(0, 0);
    glVertex3f(size, size, -size);
    glTexCoord2f(1, 0);
    glVertex3f(size, size, size);
    glTexCoord2f(1, 1);
    glVertex3f(size, -size, size);
    glTexCoord2f(0, 1);
    glVertex3f(size, -size, -size);
    glEnd(); // End of drawing color-cube
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
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//     glfwWindowHint(GLFW_SAMPLES, 4);

// #ifdef __APPLE__
//     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
// #endif

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
        // glTranslatef(0.0f, 0.0f, -7.0f);
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