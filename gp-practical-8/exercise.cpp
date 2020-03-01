#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void display();
void drawSphere();
void cube();
void light();
void light2();
void drawShadow();
void drawShadow2();

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// camera
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float zoomLevel = 0.0;
float rotateCam = 0;
float angle = 0;

float x1 = 1, y5 = 6, z1 = 1;
float x2 = 1, y2 = 6, z2 = 1;

float ambient1[] = {0, 1, 0, 0}; //ambient colour
float ambient2[] = {0, 0, 1, 0}; //ambient colour
float d[] = {0, 0, 0, 0};        //diffuse
float l1[] = {x1, y5, z1};
float l2[] = {x2, y2, z2};

void init()
{
    glEnable(GL_DEPTH_TEST); // Enable depth testing for z-culling
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

        // glMatrixMode(GL_PROJECTION);
        // glPushMatrix();
        // glLoadIdentity();

        // // glOrtho(0.0, glfwwid, 0.0, glutGet(GLUT_WINDOW_HEIGHT), -1.0, 1.0);
        // glMatrixMode(GL_MODELVIEW);
        // glPushMatrix();
        // glLoadIdentity();

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

        // glLoadIdentity();

        glTranslatef(0.0f, -5.0f, zoomLevel);
        glRotatef(20, 1, 0, 0);
        glRotatef(rotateCam, 0, 1, 0);
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

        glEnable(GL_COLOR_MATERIAL); //so won't be black&white

        //plane
        glPushMatrix();
        glColor3f(1, 0, 0);
        glRotatef(90, 1, 0, 0);
        glTranslatef(-6.5, -5, -0.5);
        glScalef(13, 10, 1);
        cube();
        glPopMatrix();

        //first sphere
        glPushMatrix();
        glTranslatef(-4, 3, 0);
        glColor3f(1, 0.5, 0.5);
        drawSphere();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-3, 3, 0);
        light();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-4, 0, 0);
        drawShadow();
        glPopMatrix();

        //second sphere
        glPushMatrix();
        glTranslatef(4, 3, 0);
        glColor3f(1, 0.5, 0.5);
        drawSphere();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(1, 3, 0);
        light2();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(4, 0, 0);
        drawShadow2();
        glPopMatrix();
    }
    glPopMatrix();
}
void drawSphere()
{
    GLUquadricObj *var = NULL;
    var = gluNewQuadric();
    gluQuadricDrawStyle(var, GLU_FILL);
    gluSphere(var, 1, 30, 10); //GLUquadricObj *, radius, slices, stacks
}

void cube()
{
    glBegin(GL_QUADS);
    //front
    glColor3f(1, 0, 1);
    glVertex3f(0, 0, 1);
    glVertex3f(1, 0, 1);
    glVertex3f(1, 0, 0);
    glVertex3f(0, 0, 0);

    //left
    glColor3f(1, 0, 1);
    glVertex3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);
    glVertex3f(0, 1, 1);

    //right
    glColor3f(1, 0, 1);
    glVertex3f(1, 0, 1);
    glVertex3f(1, 0, 0);
    glVertex3f(1, 1, 0);
    glVertex3f(1, 1, 1);

    //top
    glColor3f(1, 0, 1);
    glVertex3f(0, 0, 1);
    glVertex3f(1, 0, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(0, 1, 1);

    //bottom
    glColor3f(1, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(1, 1, 0);
    glVertex3f(0, 1, 0);

    //back
    glColor3f(1, 0, 1);
    glVertex3f(0, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, 0);
    glVertex3f(0, 1, 0);

    glEnd();
}

void light()
{
    l1[0] = x1;
    l1[1] = y5;
    l1[2] = z1;

    glLightfv(GL_LIGHT0, GL_DIFFUSE, ambient1);
    glLightfv(GL_LIGHT0, GL_POSITION, l1);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

    glPushMatrix();
    glColor3f(0, 1, 0);
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glVertex3f(x1, y5, z1);
    glEnd();
    glPopMatrix();
}
void light2()
{
    l2[0] = x2;
    l2[1] = y2;
    l2[2] = z2;

    glLightfv(GL_LIGHT1, GL_DIFFUSE, ambient2);
    glLightfv(GL_LIGHT1, GL_POSITION, l2);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);

    glPushMatrix();
    glColor3f(0, 0, 1);
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glVertex3f(x2, y2, z2);
    glEnd();
    glPopMatrix();
}
void drawShadow()
{
    GLfloat matrix[16] = {
        y5, -x1, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        0.0, -z1, y5, 0.0,
        0.0, -1, 0.0, y5};

    glPushMatrix();
    glTranslatef(0.0, 1.5, 0.0);
    glMultMatrixf(matrix);
    glRotatef(20, 1.0, 0.0, 0.0);
    //glTranslatef(0.0f, 0.0f, 0.0f);
    drawSphere();
    glPopMatrix();
}
void drawShadow2()
{
    GLfloat matrix[16] = {
        y2, -x2, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        0.0, -z2, y2, 0.0,
        0.0, -1, 0.0, y2};

    glPushMatrix();
    glTranslatef(0.0, 1.5, 0.0);
    glMultMatrixf(matrix);
    glRotatef(20, 1.0, 0.0, 0.0);
    //glTranslatef(0.0f, 0.0f, 0.0f);
    drawSphere();
    glPopMatrix();
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

            break;

        default:
            break;
        }
    }
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        rotateCam -= 10;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        rotateCam += 10;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        angle -= 10;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        angle -= 10;

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        y5 += 0.01; //W Up
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        y5 -= 0.01; //S Down
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        x1 += 0.01; //A Left
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        x1 -= 0.01; //D Right
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        z1 -= 0.01; //E Near
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
        z1 += 0.01; //Q Far

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        y2 += 0.01; //W Up
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        y2 -= 0.01; //S Down
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        x2 += 0.01; //A Left
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        x2 -= 0.01; //D Right
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        z2 -= 0.01; //E Near
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
        z2 += 0.01; //Q Far
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
