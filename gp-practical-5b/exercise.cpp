#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

GLuint *textures = new GLuint[1];
int width, height, nrChannels;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// // camera
// Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
// float lastX = SCR_WIDTH / 2.0f;
// float lastY = SCR_HEIGHT / 2.0f;
// bool firstMouse = true;

// // timing
// float deltaTime = 0.0f;
// float lastFrame = 0.0f;

GLUquadricObj *var = NULL;
double rotateCam = 0, bridgeDegree = 0;
bool isOrtho = false;

GLfloat aspect = SCR_WIDTH / SCR_HEIGHT;

GLuint LoadTexture(const char *fileName)
{
    glGenTextures(1, &textures[0]);
    glEnable(GL_TEXTURE_2D);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    // load and generate the texture
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(fileName, &width, &height, &nrChannels, 0);

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
}

void building()
{
    glBegin(GL_QUADS);
    //front
    glColor3f(0.94, 0.89, 0.69);
    glVertex3f(0, 0.6, 0);
    glVertex3f(0.3, 0.6, 0);
    glVertex3f(0.3, 0, 0);
    glVertex3f(0, 0, 0);
    //left
    glVertex3f(0, 0.6, 0);
    glVertex3f(0, 0.6, 0.3);
    glVertex3f(0, 0, 0.3);
    glVertex3f(0, 0, 0);
    //back
    glVertex3f(0, 0.6, 0.3);
    glVertex3f(0.3, 0.6, 0.3);
    glVertex3f(0.3, 0, 0.3);
    glVertex3f(0, 0, 0.3);
    //right
    glVertex3f(0.3, 0.6, 0.3);
    glVertex3f(0.3, 0.6, 0);
    glVertex3f(0.3, 0, 0);
    glVertex3f(0.3, 0, 0.3);
    //top
    glVertex3f(0, 0.6, 0.3);
    glVertex3f(0.3, 0.6, 0.3);
    glVertex3f(0.3, 0.6, 0);
    glVertex3f(0, 0.6, 0);
    //bottom
    glVertex3f(0, 0, 0.3);
    glVertex3f(0.3, 0, 0.3);
    glVertex3f(0.3, 0, 0);
    glVertex3f(0, 0, 0);
    glEnd();
}

void longBridge()
{
    glBegin(GL_QUADS);
    glColor3f(0.55, 1, 0.98);
    //front
    glVertex3f(0, 0.6, 0);
    glVertex3f(0.3, 0.6, 0);
    glVertex3f(0.3, 0, 0);
    glVertex3f(0, 0, 0);
    //left
    glVertex3f(0, 0.6, 0);
    glVertex3f(0, 0.6, 0.3);
    glVertex3f(0, 0, 0.3);
    glVertex3f(0, 0, 0);
    //back
    glVertex3f(0, 0.6, 0.3);
    glVertex3f(0.3, 0.6, 0.3);
    glVertex3f(0.3, 0, 0.3);
    glVertex3f(0, 0, 0.3);
    //right
    glVertex3f(0.3, 0.6, 0.3);
    glVertex3f(0.3, 0.6, 0);
    glVertex3f(0.3, 0, 0);
    glVertex3f(0.3, 0, 0.3);
    //top
    glVertex3f(0, 0.6, 0.3);
    glVertex3f(0.3, 0.6, 0.3);
    glVertex3f(0.3, 0.6, 0);
    glVertex3f(0, 0.6, 0);
    //bottom
    glVertex3f(0, 0, 0.3);
    glVertex3f(0.3, 0, 0.3);
    glVertex3f(0.3, 0, 0);
    glVertex3f(0, 0, 0);
    glEnd();
}

// void shortBridge()
// {
//     glBegin(GL_QUADS);
//     glColor3f(1, 0, 0);
//     //front
//     glVertex3f(0, 0.6, 0);
//     glVertex3f(0.3, 0.6, 0);
//     glVertex3f(0.3, 0, 0);
//     glVertex3f(0, 0, 0);
//     //left
//     glVertex3f(0, 0.6, 0);
//     glVertex3f(0, 0.6, 0.3);
//     glVertex3f(0, 0, 0.3);
//     glVertex3f(0, 0, 0);
//     //back
//     glVertex3f(0, 0.6, 0.3);
//     glVertex3f(0.3, 0.6, 0.3);
//     glVertex3f(0.3, 0, 0.3);
//     glVertex3f(0, 0, 0.3);
//     //right
//     glVertex3f(0.3, 0.6, 0.3);
//     glVertex3f(0.3, 0.6, 0);
//     glVertex3f(0.3, 0, 0);
//     glVertex3f(0.3, 0, 0.3);
//     //top
//     glVertex3f(0, 0.6, 0.3);
//     glVertex3f(0.3, 0.6, 0.3);
//     glVertex3f(0.3, 0.6, 0);
//     glVertex3f(0, 0.6, 0);
//     //bottom
//     glVertex3f(0, 0, 0.3);
//     glVertex3f(0.3, 0, 0.3);
//     glVertex3f(0.3, 0, 0);
//     glVertex3f(0, 0, 0);
//     glEnd();
// }

void cylinderBase()
{
    gluCylinder(var, 0.3, 0.3, 0.3, 20, 20);
}

void cylinderTop()
{
    gluCylinder(var, 0.05, 0.05, 0.65, 20, 20);
}

void coneTop()
{
    gluCylinder(var, 0, 0.07, 0.1, 40, 40);
}

void coneTopBig()
{
    gluCylinder(var, 0, 0.1, 0.2, 40, 40);
}

void bridgeString()
{
    gluCylinder(var, 0, 0.3, 0.3, 2, 3);
}

void drawBridgeCuboid(float size, float widthScale, float thinness, float longness)
{
    glBegin(GL_QUADS);
    // front
    glVertex3f(0, 0, size / widthScale);
    glVertex3f(size / thinness, 0, size / widthScale);
    glVertex3f(size / thinness, 0, 0);
    glVertex3f(0, 0, 0);

    // left
    glVertex3f(0, size * longness, size / widthScale);
    glVertex3f(0, 0, size / widthScale);
    glVertex3f(0, 0, 0);
    glVertex3f(0, size * longness, 0);

    // bottom
    glVertex3f(0, size * longness, 0);
    glVertex3f(size / thinness, size * longness, 0);
    glVertex3f(size / thinness, 0, 0);
    glVertex3f(0, 0, 0);

    // right
    glVertex3f(size / thinness, 0, size / widthScale);
    glVertex3f(size / thinness, size * longness, size / widthScale);
    glVertex3f(size / thinness, size * longness, 0);
    glVertex3f(size / thinness, 0, 0);

    // behind
    glVertex3f(size / thinness, size * longness, size / widthScale);
    glVertex3f(0, size * longness, size / widthScale);
    glVertex3f(0, size * longness, 0);
    glVertex3f(size / thinness, size * longness, 0);

    // top
    glVertex3f(0, size * longness, size / widthScale);
    glVertex3f(size / thinness, size * longness, size / widthScale);
    glVertex3f(size / thinness, 0, size / widthScale);
    glVertex3f(0, 0, size / widthScale);

    glEnd();
}

void towerBridge()
{
    var = gluNewQuadric();
    glPushMatrix();
    {
        glTranslatef(-0.6, -0.4, 0);
        building();
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0.3, 0.05, 0);
        glScalef(1, 0.20, 0.25);
        glRotatef(90, 0, 0, 1);
        longBridge();
    }
    glPopMatrix();

    // open close bridge
    glPushMatrix();
    {
        glTranslatef(-0.55, -0.4 + 0.05, 0.1);
        glRotatef(bridgeDegree, 0, 0, 1);
        glRotatef(270, 0, 0, 1);
        drawBridgeCuboid(1.5, 6, 30, 0.37);
    }
    glPopMatrix();

    // open close bridge
    glPushMatrix();
    {
        glTranslatef(0.55, -0.4, 0.1);
        glRotatef(-bridgeDegree, 0, 0, 1);
        glRotatef(-270, 0, 0, 1);
        drawBridgeCuboid(1.5, 6, 30, 0.37);
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_FILL);
        glColor3ub(0, 157, 255);
        glTranslatef(-0.45, -0.4, 0);
        glRotatef(90, 1, 0, 0);
        cylinderBase();
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_FILL);
        glColor3ub(0, 157, 255);
        glTranslatef(-0.45, 0.40, 0);
        glRotatef(90, 1, 0, 0);
        coneTopBig();
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_FILL);
        glColor3ub(255, 255, 255);
        glTranslatef(-0.55, 0.25, 0);
        glRotatef(90, 1, 0, 0);
        cylinderTop();
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_FILL);
        glColor3ub(0, 157, 255);
        glTranslatef(-0.55, 0.35, 0);
        glRotatef(90, 1, 0, 0);
        coneTop();
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_FILL);
        glColor3ub(255, 255, 255);
        glTranslatef(-0.35, 0.25, 0);
        glRotatef(90, 1, 0, 0);
        cylinderTop();
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_FILL);
        glColor3ub(0, 157, 255);
        glTranslatef(-0.35, 0.35, 0);
        glRotatef(90, 1, 0, 0);
        coneTop();
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_LINE);
        glColor3ub(255, 255, 255);
        glTranslatef(-0.6, -0.4, 0);
        glRotatef(270, 0, 1, 1);
        bridgeString();
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-0.6, -0.46, 0);
        glColor3ub(156, 250, 255);
        glRotatef(90, 0, 0, 1);
        drawBridgeCuboid(1.5, 4, 30, 0.37);
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_FILL);
        glColor3ub(0, 157, 255);
        glTranslatef(0.45, -0.4, 0);
        glRotatef(90, 1, 0, 0);
        cylinderBase();
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(1.17, -0.46, 0);
        glColor3ub(156, 250, 255);
        glRotatef(90, 0, 0, 1);
        drawBridgeCuboid(1.5, 4, 30, 0.37);
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_LINE);
        glColor3ub(255, 255, 255);
        glTranslatef(0.6, -0.4, 0);
        glRotatef(-270, 0, 1, 1);
        bridgeString();
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0.30, -0.4, 0);
        building();
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_FILL);
        glColor3ub(0, 157, 255);
        glTranslatef(0.45, 0.40, 0);
        glRotatef(90, 1, 0, 0);
        coneTopBig();
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_FILL);
        glColor3ub(255, 255, 255);
        glTranslatef(0.55, 0.25, 0);
        glRotatef(90, 1, 0, 0);
        cylinderTop();
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_FILL);
        glColor3ub(0, 157, 255);
        glTranslatef(0.55, 0.35, 0);
        glRotatef(90, 1, 0, 0);
        coneTop();
    }
    glPopMatrix();

    glPushMatrix();
    {

        gluQuadricDrawStyle(var, GLU_FILL);
        glColor3ub(255, 255, 255);
        glTranslatef(0.35, 0.25, 0);
        glRotatef(90, 1, 0, 0);
        cylinderTop();
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_FILL);
        glColor3ub(0, 157, 255);
        glTranslatef(0.35, 0.35, 0);
        glRotatef(90, 1, 0, 0);
        coneTop();
    }
    glPopMatrix();
}

void init()
{
    glClearDepth(1.0f);                                // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);                           // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);                            // Set the type of depth-test
    glShadeModel(GL_SMOOTH);                           // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Nice perspective corrections

    glPointSize(10.0);

    // LoadTexture("/home/liho/Desktop/graphic-programming/gp-practical-5b/bg.jpg");
}
void drawMoon()
{
    float x = 0, y = 0, z = -15, GL_PI = 3.142, radius = 0.4;
    glPushMatrix();
    {
        // Call only once for all remaining points
        glBegin(GL_LINES);

        // All lines lie in the xy plane.
        for (float angle = 0.0f; angle <= GL_PI; angle += (GL_PI / 50.0f))
        {
            // Top half of the circle
            x = radius * sin(angle);
            y = radius * cos(angle);
            glVertex3f(x + 1, y + 2, z); // First endpoint of line

            // Bottom half of the circle
            x = radius * sin(angle + GL_PI);
            y = radius * cos(angle + GL_PI);
            glVertex3f(x + 1, y + 2, z); // Second endpoint of line
        }
        // Done drawing points
        glEnd();
    }
    glPopMatrix();
}
void drawCirle(float x1, float y1, float radius)
{
    float x2 = x1, y2 = y1;

    glColor3ub(246, 246, 246);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x1, y1);
    for (float angle = 0; angle <= 360; angle += 10)
    {
        x2 = x1 + cos(angle) * radius;
        y2 = y1 + sin(angle) * radius;
        glVertex2f(x2, y2);
    }
    glEnd();
}
void drawCloud(float size)
{
    drawCirle(0, 0, size);
    drawCirle(0.2, 0, size);

    drawCirle(0.35, 0.1, size);

    drawCirle(0.2, 0.2, size);
    drawCirle(0, 0.2, size);

    drawCirle(-0.15, 0.1, size);
}

void drawClouds()
{
    glPushMatrix();
    {
        glTranslatef(-5, 1.5, -15);
        drawCloud(0.15);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-7, 1.2, -15);
        drawCloud(0.15);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-2, 1.5, -15);
        drawCloud(0.15);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(4, 1.2, -15);
        drawCloud(0.15);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(8, 1.5, -15);
        drawCloud(0.15);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(13, 1.2, -15);
        drawCloud(0.15);
    }
    glPopMatrix();
}

void display()
{
    // // background textureglPushMatrix();
    // glMatrixMode(GL_PROJECTION);
    // glPushMatrix();
    // glBindTexture(GL_TEXTURE_2D, textures[0]);
    // glBegin(GL_QUADS);

    // glTexCoord2f(0, 0);
    // glVertex2f(-1, -1);
    // glTexCoord2f(1, 0);
    // glVertex2f(1, -1);
    // glTexCoord2f(1, 1);
    // glVertex2f(1, 1);
    // glTexCoord2f(0, 1);
    // glVertex2f(-1, 1);
    // glEnd();

    // glBindTexture(GL_TEXTURE_2D, 0);
    // glPopMatrix();glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -4.0);
    glRotatef(180, 0.0, 1.0, 0.0);
    glRotatef(-rotateCam, 0.0, 1.0, 0.0);

    glPushMatrix();
    {
        towerBridge();
    }
    glPopMatrix();

    glPushMatrix();
    {
        glColor3ub(252, 212, 64);
        glTranslatef(0, 5, 0);

        drawMoon();
    }
    glPopMatrix();
    glPushMatrix();
    {
        glColor3ub(252, 212, 64);
        glTranslatef(0, 5, 0);
        glRotatef(185, 0.0, 1.0, 0.0);

        drawMoon();
    }
    glPopMatrix();
    glPushMatrix();
    {
        drawClouds();
    }
    glPopMatrix();
    glPushMatrix();
    {
        glRotatef(185, 0.0, 1.0, 0.0);
        drawClouds();
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
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // configure global opengl state
    // -----------------------------
    init();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // float currentFrame = glfwGetTime();
        // deltaTime = currentFrame - lastFrame;
        // lastFrame = currentFrame;

        processInput(window);
        // rotateCam = glfwGetTime() * 90.0;
        // render
        // ------
        if (!isOrtho)
        {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-2 * aspect, 2 * aspect, -2, 2, -7, 7);
        }
        else
        {
            // Set the aspect ratio of the clipping volume to match the viewport
            glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
            glLoadIdentity();            // Reset
            // Enable perspective projection with fovy, aspect, zNear and zFar

            gluPerspective(45.0f, aspect, 0.1f, 100.0f);
        }
        // camera/view transformation
        // glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        // float radius = 10.0f;
        // float camX   = sin(glfwGetTime()) * radius;
        // float camZ   = cos(glfwGetTime()) * radius;
        // glm::mat4 view2 = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(2.0f, 0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        // gluLookAt(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
        // gluLookAt(0.0, 0.0f, 1.0f, 0.0f, 0.0f, -5.0f, 0.0f, 1.0f, -1.0f);
        // std::cout << view2[3].x <<std::endl;
        // glm::mat4 view = camera.GetViewMatrix();
        // gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, cameraPos.x + cameraFront.x, cameraPos.y + cameraFront.y, cameraPos.z + cameraFront.z,  0.0, 1.0, 0.0);
        // gluLookAt(view[0].x, view[0].y, view[0].z, view[0].x + view[1].x, view[0].y + view[1].y, view[0].z + view[1].z, view[2].x, view[2].y, view[2].z);
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
    glfwTerminate();
    return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    if (height == 0)
        height = 1; // To prevent divide by 0
    aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // if (!isOrtho)
    // {
    //     glMatrixMode(GL_PROJECTION);
    //     glLoadIdentity();
    //     glOrtho(-2 * aspect, 2 * aspect, -2, 2, -2, 2);
    // }
    // else
    // {
    //     // Set the aspect ratio of the clipping volume to match the viewport
    //     glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
    //     glLoadIdentity();            // Reset
    //     // Enable perspective projection with fovy, aspect, zNear and zFar

    //     gluPerspective(45.0f, aspect, 0.1f, 100.0f);
    // }
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    // if (firstMouse)
    // {
    //     lastX = xpos;
    //     lastY = ypos;
    //     firstMouse = false;
    // }

    // float xoffset = xpos - lastX;
    // float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    // lastX = xpos;
    // lastY = ypos;

    // camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    // camera.ProcessMouseScroll(yoffset);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{

    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_O:
            isOrtho = !isOrtho;
        default:
            break;
        }
    }
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
        if (bridgeDegree < 37)
            bridgeDegree += 1;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        if (bridgeDegree > 0)
            bridgeDegree -= 1;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        rotateCam = 0;
        bridgeDegree = 0;
    }
    // if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    //     camera.ProcessKeyboard(FORWARD, deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    //     camera.ProcessKeyboard(BACKWARD, deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    //     camera.ProcessKeyboard(LEFT, deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    //     camera.ProcessKeyboard(RIGHT, deltaTime);
}