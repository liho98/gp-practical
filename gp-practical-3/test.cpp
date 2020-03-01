#include <GLFW/glfw3.h>
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

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

float degToRad(float deg)
{
    return deg * (M_PI / 180);
}

void drawQ1()
{
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-translateX, translateY, 0.0f);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(-0.25, 0.15);
    glVertex2f(0.25, 0.15);
    glVertex2f(0.25, -0.15);
    glVertex2f(-0.25, -0.15);
    glEnd();
    glPopMatrix();

    glTranslatef(translateX, -translateY, 0.0f);
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

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

int main(void)
{
    GLFWwindow *window;

    glfwWindowHint(GLFW_SAMPLES,4);

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "Practical 3", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    glEnable(GL_TEXTURE_2D);

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

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

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

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
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

    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        translateX -= 0.005;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        translateX -= 0.005;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        translateY -= 0.005;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        translateY -= 0.005;
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        background = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        background = 1;
    }

}