#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <GL/glu.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos);


GLuint LoadJpgTexture(const char *filename[], GLuint *texture, int size);
GLuint LoadPngTexture(const char *filename[], GLuint *texture, int size);
GLuint LoadBmpTexture(const char *filename[], GLuint *texture, int size);

void drawCube(float size);
void drawPyramid(float size);
void drawIceCream();
void drawTowerBridge();
void display();

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

float zoomLevel = -0.3f;

const char *bmpFilenames[] = {
    "/home/liho/Desktop/graphic-programming/gp-practical-7/res/bmp/Brick.bmp",
    "/home/liho/Desktop/graphic-programming/gp-practical-7/res/bmp/Box.bmp",
    "/home/liho/Desktop/graphic-programming/gp-practical-7/res/bmp/Metal.bmp",
    "/home/liho/Desktop/graphic-programming/gp-practical-7/res/bmp/Wood.bmp",
    "/home/liho/Desktop/graphic-programming/gp-practical-7/res/bmp/sky.bmp"
};
const char *jpgFilenames[] = {
    "/home/liho/Desktop/graphic-programming/gp-practical-7/res/jpg&png/cone.jpg",
    "/home/liho/Desktop/graphic-programming/gp-practical-7/res/jpg&png/ice-cream-2.jpg",
    "/home/liho/Desktop/graphic-programming/gp-practical-7/res/jpg&png/grape.jpg",
    "/home/liho/Desktop/graphic-programming/gp-practical-7/res/jpg&png/chocolate.jpg",
    "/home/liho/Desktop/graphic-programming/gp-practical-7/res/jpg&png/bg.jpg",
    "/home/liho/Desktop/graphic-programming/gp-practical-7/res/bmp/sky.jpg"};

const char *pngFilenames[] = {"/home/liho/Desktop/graphic-programming/gp-practical-7/res/jpg&png/tzuyu-coverjpg.png"};

GLuint *bmpTextures = new GLuint[4];
GLuint *jpgTextures = new GLuint[5];
GLuint *pngTextures = new GLuint[5];
int width, height, nrChannels;

bool rotate = true;

bool pyramid = false, rotateClockwise = true;
int bmpTextureIndex = 0, textureIndex = 0;

float rotateObj[] = {0.0, 0.0, 0.0, 0.0};
float rotateObj1 = 0.0;

char question = '1';

GLUquadricObj *var = NULL;
double rotateCam = 0, bridgeDegree = 0;
bool isOrtho = false;

// camera
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
// camera
bool firstMouse = false;
float xPosf = 0.0, yPosf = 0.0;

void init()
{
    glEnable(GL_DEPTH_TEST); // Enable depth testing for z-culling

    glEnable(GL_TEXTURE_2D);
    // std::cout << sizeof(textures) << std::endl;
    LoadBmpTexture(bmpFilenames, bmpTextures, (sizeof(bmpFilenames) / sizeof(*bmpFilenames)));
    LoadJpgTexture(jpgFilenames, jpgTextures, (sizeof(jpgFilenames) / sizeof(*jpgFilenames)));
    LoadPngTexture(pngFilenames, pngTextures, (sizeof(pngFilenames) / sizeof(*pngFilenames)));
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
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // configure global opengl state
    // -----------------------------
    init();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        // rotateObj[0] = sin(glfwGetTime()) * 90.0;
        // render
        // ------
        // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // // background texture


        // // glOrtho(0.0, glfwwid, 0.0, glutGet(GLUT_WINDOW_HEIGHT), -1.0, 1.0);


        // glBindTexture(GL_TEXTURE_2D, jpgTextures[4]);
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
        // glDeleteTextures(0, &jpgTextures[4]);
        // glPopMatrix();
        // glMatrixMode(GL_PROJECTION);
        // glPopMatrix();
        // gluLookAt(camera.x, camera.y, camera.z,  lookat.x, lookat.y, lookat.z, 0, 1, 0);


        glPushMatrix();
        glMatrixMode(GL_MODELVIEW); // To operate on model-view matrix

glPopMatrix();
        glLoadIdentity();
    GLUquadricObj *sphere = NULL;
    sphere = gluNewQuadric();
    gluQuadricTexture(sphere, GLU_TRUE);
    gluQuadricDrawStyle(sphere, GLU_FILL);
    glBindTexture(GL_TEXTURE_2D, jpgTextures[5]);
    gluSphere(sphere, 95, 40, 40);
    gluDeleteQuadric(sphere);

glBindTexture(GL_TEXTURE_2D, 0);
glPopMatrix();
        glTranslatef(0.0f, 0.0f, zoomLevel);



        display();
        glPopMatrix();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glDisable(GL_TEXTURE_2D);

    glfwTerminate();
    return 0;
}

void display()
{
    glPushMatrix();
    {
        if (rotate)
        {
            glRotatef(-rotateObj[0], rotateObj[1], rotateObj[2], rotateObj[3]);
        }
        else
        {
            glRotatef(rotateObj[0], rotateObj[1], rotateObj[2], rotateObj[3]);
        }

        if (rotateClockwise)
        {
            glRotatef(-rotateObj[0], rotateObj[1], rotateObj[2], rotateObj[3]);
        }
        else
        {
            glRotatef(rotateObj[0], rotateObj[1], rotateObj[2], rotateObj[3]);
        }

        switch (question)
        {
        case '1':
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, bmpTextures[0]);
            glPushMatrix();
            drawPyramid(0.6);
            glPopMatrix();
            glBindTexture(GL_TEXTURE_2D, 0);
            break;
        case '2':
            glBindTexture(GL_TEXTURE_2D, bmpTextures[bmpTextureIndex]);
            glPushMatrix();
            drawCube(0.6);
            glPopMatrix();
            glBindTexture(GL_TEXTURE_2D, 0);

            break;
        case '3':
            glPushMatrix();
            drawIceCream();
            glPopMatrix();
            gluDeleteQuadric(var);
            break;
        case '4':
            glPushMatrix();
            drawTowerBridge();
            glPopMatrix();
            gluDeleteQuadric(var);
            break;
        default:
            break;
        }
    }
    glPopMatrix();
}

void building()
{
    glBegin(GL_QUADS);
    //front
    // glColor3f(0.94, 0.89, 0.69);
    glTexCoord2f(1, 1);
    glVertex3f(0, 0.6, 0);
    glTexCoord2f(0, 1);
    glVertex3f(0.3, 0.6, 0);
    glTexCoord2f(0, 0);
    glVertex3f(0.3, 0, 0);
    glTexCoord2f(1, 0);
    glVertex3f(0, 0, 0);

    //left
    glTexCoord2f(1, 1);
    glVertex3f(0, 0.6, 0);
    glTexCoord2f(0, 1);
    glVertex3f(0, 0.6, 0.3);
    glTexCoord2f(0, 0);
    glVertex3f(0, 0, 0.3);
    glTexCoord2f(1, 0);
    glVertex3f(0, 0, 0);
    //back
    glTexCoord2f(1, 1);
    glVertex3f(0, 0.6, 0.3);
    glTexCoord2f(0, 1);
    glVertex3f(0.3, 0.6, 0.3);
    glTexCoord2f(0, 0);
    glVertex3f(0.3, 0, 0.3);
    glTexCoord2f(1, 0);
    glVertex3f(0, 0, 0.3);
    //right
    glTexCoord2f(1, 1);
    glVertex3f(0.3, 0.6, 0.3);
    glTexCoord2f(0, 1);
    glVertex3f(0.3, 0.6, 0);
    glTexCoord2f(0, 0);
    glVertex3f(0.3, 0, 0);
    glTexCoord2f(1, 0);
    glVertex3f(0.3, 0, 0.3);
    //top
    glTexCoord2f(1, 1);
    glVertex3f(0, 0.6, 0.3);
    glTexCoord2f(0, 1);
    glVertex3f(0.3, 0.6, 0.3);
    glTexCoord2f(0, 0);
    glVertex3f(0.3, 0.6, 0);
    glTexCoord2f(1, 0);
    glVertex3f(0, 0.6, 0);
    //bottom
    glTexCoord2f(1, 1);
    glVertex3f(0, 0, 0.3);
    glTexCoord2f(0, 1);
    glVertex3f(0.3, 0, 0.3);
    glTexCoord2f(0, 0);
    glVertex3f(0.3, 0, 0);
    glTexCoord2f(1, 0);
    glVertex3f(0, 0, 0);
    glEnd();
}

void longBridge()
{
    glBegin(GL_QUADS);
    // glColor3f(0.55, 1, 0.98);
    //front
    glTexCoord2f(0, 0);
    glVertex3f(0, 0.6, 0);
    glTexCoord2f(1, 0);
    glVertex3f(0.3, 0.6, 0);
    glTexCoord2f(1, 1);
    glVertex3f(0.3, 0, 0);
    glTexCoord2f(0, 1);
    glVertex3f(0, 0, 0);
    //left
    glTexCoord2f(0, 0);
    glVertex3f(0, 0.6, 0);
    glTexCoord2f(1, 0);
    glTexCoord2f(1, 0);
    glVertex3f(0, 0.6, 0.3);
    glTexCoord2f(1, 1);
    glVertex3f(0, 0, 0.3);
    glTexCoord2f(0, 1);
    glVertex3f(0, 0, 0);
    //back
    glTexCoord2f(0, 0);
    glVertex3f(0, 0.6, 0.3);
    glTexCoord2f(1, 0);
    glTexCoord2f(1, 0);
    glVertex3f(0.3, 0.6, 0.3);
    glTexCoord2f(1, 1);
    glVertex3f(0.3, 0, 0.3);
    glTexCoord2f(0, 1);
    glVertex3f(0, 0, 0.3);
    //right
    glTexCoord2f(0, 0);
    glVertex3f(0.3, 0.6, 0.3);
    glTexCoord2f(1, 0);
    glVertex3f(0.3, 0.6, 0);
    glTexCoord2f(1, 1);
    glVertex3f(0.3, 0, 0);
    glTexCoord2f(0, 1);
    glVertex3f(0.3, 0, 0.3);
    //top
    glTexCoord2f(0, 0);
    glVertex3f(0, 0.6, 0.3);
    glTexCoord2f(1, 0);
    glVertex3f(0.3, 0.6, 0.3);
    glTexCoord2f(1, 1);
    glVertex3f(0.3, 0.6, 0);
    glTexCoord2f(0, 1);
    glVertex3f(0, 0.6, 0);
    //bottom
    glTexCoord2f(0, 0);
    glVertex3f(0, 0, 0.3);
    glTexCoord2f(1, 0);
    glVertex3f(0.3, 0, 0.3);
    glTexCoord2f(1, 1);
    glVertex3f(0.3, 0, 0);
    glTexCoord2f(0, 1);
    glVertex3f(0, 0, 0);
    glEnd();
}

void cylinderBase()
{
    glBindTexture(GL_TEXTURE_2D, jpgTextures[1]);
    gluCylinder(var, 0.3, 0.3, 0.3, 20, 20);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void cylinderTop()
{
    glBindTexture(GL_TEXTURE_2D, jpgTextures[2]);
    gluCylinder(var, 0.05, 0.05, 0.65, 20, 20);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void coneTop()
{
    glBindTexture(GL_TEXTURE_2D, jpgTextures[0]);
    gluCylinder(var, 0, 0.07, 0.1, 40, 40);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void coneTopBig()
{
    glBindTexture(GL_TEXTURE_2D, jpgTextures[1]);
    gluCylinder(var, 0, 0.1, 0.2, 40, 40);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void bridgeString()
{
    gluCylinder(var, 0, 0.3, 0.3, 2, 3);
}

void drawBridgeCuboid(float size, float widthScale, float thinness, float longness)
{
    glBegin(GL_QUADS);
    // front
    glTexCoord2f(0, 0);
    glVertex3f(0, 0, size / widthScale);
    glTexCoord2f(1, 0);
    glVertex3f(size / thinness, 0, size / widthScale);
    glTexCoord2f(1, 1);
    glVertex3f(size / thinness, 0, 0);
    glTexCoord2f(0, 1);
    glVertex3f(0, 0, 0);

    // left
    glTexCoord2f(0, 0);
    glVertex3f(0, size * longness, size / widthScale);
    glTexCoord2f(1, 0);
    glVertex3f(0, 0, size / widthScale);
    glTexCoord2f(1, 1);
    glVertex3f(0, 0, 0);
    glTexCoord2f(0, 1);
    glVertex3f(0, size * longness, 0);

    // bottom
    glTexCoord2f(0, 0);
    glVertex3f(0, size * longness, 0);
    glTexCoord2f(1, 0);
    glVertex3f(size / thinness, size * longness, 0);
    glTexCoord2f(1, 1);
    glVertex3f(size / thinness, 0, 0);
    glTexCoord2f(0, 1);
    glVertex3f(0, 0, 0);

    // right
    glTexCoord2f(0, 0);
    glVertex3f(size / thinness, 0, size / widthScale);
    glTexCoord2f(1, 0);
    glVertex3f(size / thinness, size * longness, size / widthScale);
    glTexCoord2f(1, 1);
    glVertex3f(size / thinness, size * longness, 0);
    glTexCoord2f(0, 1);
    glVertex3f(size / thinness, 0, 0);

    // behind
    glTexCoord2f(0, 0);
    glVertex3f(size / thinness, size * longness, size / widthScale);
    glTexCoord2f(1, 0);
    glVertex3f(0, size * longness, size / widthScale);
    glTexCoord2f(1, 1);
    glVertex3f(0, size * longness, 0);
    glTexCoord2f(0, 1);
    glVertex3f(size / thinness, size * longness, 0);

    // top
    glTexCoord2f(0, 0);
    glVertex3f(0, size * longness, size / widthScale);
    glTexCoord2f(1, 0);
    glVertex3f(size / thinness, size * longness, size / widthScale);
    glTexCoord2f(1, 1);
    glVertex3f(size / thinness, 0, size / widthScale);
    glTexCoord2f(0, 1);
    glVertex3f(0, 0, size / widthScale);

    glEnd();
}

void drawTowerBridge()
{
    var = gluNewQuadric();
    gluQuadricTexture(var, GL_TRUE);

    glPushMatrix();
    {
        glTranslatef(-0.6, -0.4, 0);
        glBindTexture(GL_TEXTURE_2D, pngTextures[0]);
        building();
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0.3, 0.05, 0);
        glScalef(1, 0.20, 0.25);
        glRotatef(90, 0, 0, 1);
        glBindTexture(GL_TEXTURE_2D, bmpTextures[3]);
        longBridge();
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    glPopMatrix();

    // open close bridge
    glPushMatrix();
    {
        glTranslatef(-0.55, -0.4 + 0.05, 0.1);
        glRotatef(bridgeDegree, 0, 0, 1);
        glRotatef(270, 0, 0, 1);
        glBindTexture(GL_TEXTURE_2D, bmpTextures[2]);
        drawBridgeCuboid(1.5, 6, 30, 0.37);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    glPopMatrix();

    // open close bridge
    glPushMatrix();
    {
        glTranslatef(0.55, -0.4, 0.1);
        glRotatef(-bridgeDegree, 0, 0, 1);
        glRotatef(-270, 0, 0, 1);
        glBindTexture(GL_TEXTURE_2D, bmpTextures[2]);
        drawBridgeCuboid(1.5, 6, 30, 0.37);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_FILL);
        // glColor3ub(0, 157, 255);
        glTranslatef(-0.45, -0.4, 0);
        glRotatef(90, 1, 0, 0);
        cylinderBase();
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_FILL);
        // glColor3ub(0, 157, 255);
        glTranslatef(-0.45, 0.40, 0);
        glRotatef(90, 1, 0, 0);
        coneTopBig();
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_FILL);
        // glColor3ub(255, 255, 255);
        glTranslatef(-0.55, 0.25, 0);
        glRotatef(90, 1, 0, 0);
        cylinderTop();
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_FILL);
        // glColor3ub(0, 157, 255);
        glTranslatef(-0.55, 0.35, 0);
        glRotatef(90, 1, 0, 0);
        coneTop();
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_FILL);
        // glColor3ub(255, 255, 255);
        glTranslatef(-0.35, 0.25, 0);
        glRotatef(90, 1, 0, 0);
        cylinderTop();
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_FILL);
        // glColor3ub(0, 157, 255);
        glTranslatef(-0.35, 0.35, 0);
        glRotatef(90, 1, 0, 0);
        coneTop();
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_LINE);
        // glColor3ub(255, 255, 255);
        glTranslatef(-0.6, -0.4, 0);
        glRotatef(270, 0, 1, 1);
        bridgeString();
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-0.6, -0.46, 0);
        // glColor3ub(156, 250, 255);
        glRotatef(90, 0, 0, 1);
        glBindTexture(GL_TEXTURE_2D, bmpTextures[2]);
        drawBridgeCuboid(1.5, 4, 30, 0.37);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_FILL);
        // glColor3ub(0, 157, 255);
        glTranslatef(0.45, -0.4, 0);
        glRotatef(90, 1, 0, 0);
        cylinderBase();
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(1.17, -0.46, 0);
        // glColor3ub(156, 250, 255);
        glRotatef(90, 0, 0, 1);
        glBindTexture(GL_TEXTURE_2D, bmpTextures[2]);
        drawBridgeCuboid(1.5, 4, 30, 0.37);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_LINE);
        // glColor3ub(255, 255, 255);
        glTranslatef(0.6, -0.4, 0);
        glRotatef(-270, 0, 1, 1);
        bridgeString();
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0.30, -0.4, 0);
        glBindTexture(GL_TEXTURE_2D, pngTextures[0]);
        building();
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_FILL);
        // glColor3ub(0, 157, 255);
        glTranslatef(0.45, 0.40, 0);
        glRotatef(90, 1, 0, 0);
        coneTopBig();
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_FILL);
        // glColor3ub(255, 255, 255);
        glTranslatef(0.55, 0.25, 0);
        glRotatef(90, 1, 0, 0);
        cylinderTop();
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_FILL);
        // glColor3ub(0, 157, 255);
        glTranslatef(0.55, 0.35, 0);
        glRotatef(90, 1, 0, 0);
        coneTop();
    }
    glPopMatrix();

    glPushMatrix();
    {

        gluQuadricDrawStyle(var, GLU_FILL);
        // glColor3ub(255, 255, 255);
        glTranslatef(0.35, 0.25, 0);
        glRotatef(90, 1, 0, 0);
        cylinderTop();
    }
    glPopMatrix();

    glPushMatrix();
    {
        gluQuadricDrawStyle(var, GLU_FILL);
        // glColor3ub(0, 157, 255);
        glTranslatef(0.35, 0.35, 0);
        glRotatef(90, 1, 0, 0);
        coneTop();
    }
    glPopMatrix();
}

void drawIceCream()
{
    var = gluNewQuadric();
    gluQuadricTexture(var, GL_TRUE);

    // cream topping
    gluQuadricDrawStyle(var, GLU_FILL);
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glTranslatef(-0.1, 0, 1.3);
    gluCylinder(var, 0.05, 0.05, 0.1, 40, 40);
    glPopMatrix();

    // cream topping
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glTranslatef(-0.1, 0, 1);
    gluCylinder(var, 0.05, 0.05, 0.1, 40, 40);
    glPopMatrix();

    // chocolate topping
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glTranslatef(-0.1, 0, 0.8);
    glBindTexture(GL_TEXTURE_2D, jpgTextures[3]);
    gluCylinder(var, 0.05, 0.05, 0.8, 20, 20);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    // fruit topping
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glTranslatef(0.3, 0, -1);
    glBindTexture(GL_TEXTURE_2D, jpgTextures[2]);
    gluSphere(var, 0.2, 20, 20);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    // top scope
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glTranslatef(0, 0, -0.5);
    glBindTexture(GL_TEXTURE_2D, jpgTextures[1]);
    gluSphere(var, 0.5, 20, 20);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    // top topping
    gluQuadricDrawStyle(var, GLU_POINT);
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glTranslatef(0, 0, -0.5);
    gluSphere(var, 0.5, 20, 20);
    glPopMatrix();

    // bottom scope
    gluQuadricDrawStyle(var, GLU_FILL);
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, jpgTextures[1]);
    gluSphere(var, 0.6, 20, 20);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    // cone
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glTranslatef(0, 0, -2);
    glBindTexture(GL_TEXTURE_2D, jpgTextures[0]);
    gluCylinder(var, 0.001, 0.6, 2, 20, 20);
    glBindTexture(GL_TEXTURE_2D, 0);

    // cone line
    // gluQuadricDrawStyle(var, GLU_LINE);
    // glColor3f(0.94, 0.91, 0.87);
    // gluCylinder(var, 0.001, 0.50, 1.66, 25, 10);
    // glPopMatrix();
}

void drawPyramid(float size)
{
    glBegin(GL_POLYGON);

    // Bottom face
    // glColor3f(1.0f, 0.5f, 0.0f); // Orange
    glTexCoord2f(0, 0); //bottom left
    glVertex3f(size, -size, size);
    glTexCoord2f(1, 0); //top left
    glVertex3f(-size, -size, size);
    glTexCoord2f(1, 1); //top right
    glVertex3f(-size, -size, -size);
    glTexCoord2f(0, 1); //bottom right
    glVertex3f(size, -size, -size);

    glEnd();

    glBegin(GL_TRIANGLES);
    // Left face
    // glColor3f(0.0f, 0.0f, 1.0f); // Blue
    glTexCoord2f(0, 0); //bottom left
    glVertex3f(0.0f, size, 0.0f);
    glTexCoord2f(1, 1); //top right
    glVertex3f(-size, -size, -size);
    glTexCoord2f(0, 1); //bottom right
    glVertex3f(-size, -size, size);

    // Back face
    // glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    glTexCoord2f(0, 0); //bottom left
    glVertex3f(0.0f, size, 0.0f);
    glTexCoord2f(1, 1); //top right
    glVertex3f(-size, -size, -size);
    glTexCoord2f(0, 1); //bottom right
    glVertex3f(size, -size, -size);

    // Right face
    // glColor3f(1.0f, 0.0f, 1.0f); // Magenta
    glTexCoord2f(0, 0); //bottom left
    glVertex3f(0.0f, size, 0.0f);
    glTexCoord2f(1, 1); //top right
    glVertex3f(size, -size, size);
    glTexCoord2f(0, 1); //bottom right
    glVertex3f(size, -size, -size);

    // Front face
    // glColor3f(1.0f, 0.0f, 0.0f); // Red
    glTexCoord2f(0, 0); //bottom left
    glVertex3f(0.0f, size, 0.0f);
    glTexCoord2f(1, 1); //top right
    glVertex3f(size, -size, size);
    glTexCoord2f(0, 1); //bottom right
    glVertex3f(-size, -size, size);

    glEnd();
}

void drawCube(float size)
{
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

GLuint LoadJpgTexture(const char *filename[], GLuint *texture, int size)
{
    // set the texture wrapping/filtering options (on the currently bound texture object)
    // load and generate the texture
    unsigned char *data;
    stbi_set_flip_vertically_on_load(true);
    for (int i = 0; i < size; i++)
    {
        data = stbi_load(filename[i], &width, &height, &nrChannels, 0);
        if (data)
        {
            glGenTextures(1, &texture[i]);
            glBindTexture(GL_TEXTURE_2D, texture[i]);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            // glDeleteTextures(1, &textureBuffer[i]);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

GLuint LoadPngTexture(const char *filename[], GLuint *texture, int size)
{
    // set the texture wrapping/filtering options (on the currently bound texture object)
    // load and generate the texture
    unsigned char *data;
    stbi_set_flip_vertically_on_load(true);
    for (int i = 0; i < size; i++)
    {
        data = stbi_load(filename[i], &width, &height, &nrChannels, 0);
        if (data)
        {
            glGenTextures(1, &texture[i]);
            glBindTexture(GL_TEXTURE_2D, texture[i]);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            // glDeleteTextures(1, &textureBuffer[i]);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

GLuint LoadBmpTexture(const char *filename[], GLuint *texture, int size)
{
    // set the texture wrapping/filtering options (on the currently bound texture object)
    // load and generate the texture
    unsigned char *data;
    stbi_set_flip_vertically_on_load(true);
    for (int i = 0; i < size; i++)
    {
        data = stbi_load(filename[i], &width, &height, &nrChannels, 0);
        if (data)
        {
            glGenTextures(1, &texture[i]);
            glBindTexture(GL_TEXTURE_2D, texture[i]);

            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            // glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // default

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            // glDeleteTextures(1, &textureBuffer[i]);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
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
            break;
        case GLFW_KEY_LEFT:
            bmpTextureIndex = (bmpTextureIndex + 4 - 1) % 4;
            break;
        case GLFW_KEY_RIGHT:
            bmpTextureIndex = (bmpTextureIndex + 4 + 1) % 4;
            break;
        case GLFW_KEY_1:
            question = '1';
            break;
        case GLFW_KEY_2:
            question = '2';
            break;
        case GLFW_KEY_3:
            question = '3';
            break;
        case GLFW_KEY_4:
            question = '4';
            break;
        default:
            break;
        }
    }
}

void processInput(GLFWwindow *window)
{

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
        rotateObj[1] = 0.0;
        rotateObj[2] = 1.0;
        rotateObj[3] = 0.0;

		rotateObj[0]  += xPosf - lastX;
		lastX = xPosf;
		lastY = yPosf;
	}    
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        pyramid = false;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        pyramid = true;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        rotateClockwise = true;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        rotateClockwise = false;
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        rotateObj[0] += 1.0;
        rotateObj[1] = 1.0;
        rotateObj[2] = 0.0;
        rotateObj[3] = 0.0;
    }

    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        rotateObj[0] += 1.0;
        rotateObj[1] = 0.0;
        rotateObj[2] = 1.0;
        rotateObj[3] = 0.0;
    }

    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        rotateObj[0] += 1.0;
        rotateObj[1] = 0.0;
        rotateObj[2] = 0.0;
        rotateObj[3] = 1.0;
    }
}
// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    // camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    // camera.ProcessMouseScroll(yoffset);
    zoomLevel += yoffset;
}

void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos)
{
	xPosf = xPos;
	yPosf = yPos;
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		lastX = xPosf;
		lastY = yPosf;
	}
}