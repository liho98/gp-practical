#include <GL/freeglut.h> // GLUT, include glu.h and gl.h
#include <math.h>
#include <iostream>
#include <SOIL.h>

/* Global variables */
char title[] = "Practical 1 exercise";
GLuint texture;
bool isDrawFlag = true, isDrawAngryBird = false;

float degToRad(float deg)
{
    return deg * (M_PI / 180);
}

/*  Initialize alpha blending function.  */
void init(void)
{
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_MULTISAMPLE);
    glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
    GLint bufs, samples;
    glGetIntegerv(GL_SAMPLE_BUFFERS, &bufs);
    glGetIntegerv(GL_SAMPLES, &samples);
    printf("MSAA on, GL_SAMPLE_BUFFERS = %d, GL_SAMPLES = %d\n", bufs, samples);

    // glEnable (GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);

    // glHint (GL_POINT_SMOOTH, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    // glPointSize(10);
}

void drawPahangFlag()
{
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-0.5, 0.25, 0);
    glVertex3f(0.5, 0.25, 0);
    glVertex3f(0.5, 0, 0);
    glVertex3f(-0.5, 0, 0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.5, 0, 0);
    glVertex3f(0.5, 0, 0);
    glVertex3f(0.5, -0.25, 0);
    glVertex3f(-0.5, -0.25, 0);
    glEnd();

    //outline
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.5, 0.25, 0);
    glVertex3f(0.5, 0.25, 0);
    glVertex3f(0.5, -0.25, 0);
    glVertex3f(-0.5, -0.25, 0);
    glEnd();
}

void drawNSFlag()
{
    glBegin(GL_QUADS);
    glColor3f(255.0f / 255, 209.0f / 255, 0.0f / 255);
    glVertex3f(-0.5, 0.25, 0);
    glVertex3f(0.5, 0.25, 0);
    glVertex3f(0.5, -0.25, 0);
    glVertex3f(-0.5, -0.25, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f / 255, 0.0f / 255, 0.0f / 255);
    glVertex3f(-0.5, 0.25, 0);
    glVertex3f(-0.5, 0, 0);
    glVertex3f(0.0, 0, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(255.0f / 255, 0.0f / 255, 0.0f / 255);
    glVertex3f(-0.5, 0.25, 0);
    glVertex3f(0, 0.25, 0);
    glVertex3f(0.0, 0, 0);
    glEnd();
}

void drawEnglandFlag()
{
    glBegin(GL_QUADS);
    glColor3f(255.0f / 255, 255.0f / 255, 255.0f / 255);
    glVertex3f(-0.5, 0.25, 0);
    glVertex3f(0.5, 0.25, 0);
    glVertex3f(0.5, -0.25, 0);
    glVertex3f(-0.5, -0.25, 0);
    glEnd();

    //top grey
    glBegin(GL_POLYGON);
    glColor4f(169.0f / 255, 169.0f / 255, 169.0f / 255, 0.5);
    glVertex3f(-0.5, 0.25, 0);
    glVertex3f(0.5, 0.25, 0);
    glColor4f(255.0f / 255, 255.0f / 255, 255.0f / 255, 0.0);
    glVertex3f(0.5, 0.15, 0);
    glVertex3f(-0.5, 0.15, 0);
    glEnd();

    //bottom grey
    glBegin(GL_POLYGON);
    glColor4f(169.0f / 255, 169.0f / 255, 169.0f / 255, 0.5);
    glVertex3f(0.5, -0.25, 0);
    glVertex3f(-0.5, -0.25, 0);
    glColor4f(255.0f / 255, 255.0f / 255, 255.0f / 255, 0.0);
    glVertex3f(-0.5, -0.15, 0);
    glVertex3f(0.5, -0.15, 0);
    glEnd();

    //left grey
    glBegin(GL_POLYGON);
    glColor4f(169.0f / 255, 169.0f / 255, 169.0f / 255, 0.5);
    glVertex3f(-0.5, 0.25, 0);
    glVertex3f(-0.5, -0.25, 0);
    glColor4f(255.0f / 255, 255.0f / 255, 255.0f / 255, 0.0);
    glVertex3f(-0.4, -0.25, 0);
    glVertex3f(-0.4, 0.25, 0);
    glEnd();

    //right grey
    glBegin(GL_POLYGON);
    glColor4f(169.0f / 255, 169.0f / 255, 169.0f / 255, 0.5);
    glVertex3f(0.5, 0.25, 0);
    glVertex3f(0.5, -0.25, 0);
    glColor4f(255.0f / 255, 255.0f / 255, 255.0f / 255, 0.0);
    glVertex3f(0.4, -0.25, 0);
    glVertex3f(0.4, 0.25, 0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(165.0f / 255, 0.0f / 255, 2.0f / 255);
    glVertex3f(-0.08, 0.25, 0);
    glVertex3f(0.08, 0.25, 0);
    glVertex3f(0.08, -0.25, 0);
    glVertex3f(-0.08, -0.25, 0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(165.0f / 255, 0.0f / 255, 2.0f / 255);
    glVertex3f(-0.5, 0.07, 0);
    glVertex3f(0.5, 0.07, 0);
    glVertex3f(0.5, -0.07, 0);
    glVertex3f(-0.5, -0.07, 0);
    glEnd();
}

void drawScotlandFlag()
{
    glBegin(GL_QUADS);
    glColor3f(255.0f / 255, 255.0f / 255, 255.0f / 255);
    glVertex3f(-0.5, 0.25, 0);
    glVertex3f(0.5, 0.25, 0);
    glVertex3f(0.5, -0.25, 0);
    glVertex3f(-0.5, -0.25, 0);
    glEnd();

    //left triangle
    glBegin(GL_POLYGON);
    glColor3f(0.0f / 255, 101.0f / 255, 191.0f / 255);
    glVertex3f(-0.5, 0.18, 0);
    glVertex3f(-0.5, -0.18, 0);
    glVertex3f(-0.17, 0.0, 0);
    glEnd();

    //right triangle
    glBegin(GL_POLYGON);
    glColor3f(0.0f / 255, 101.0f / 255, 191.0f / 255);
    glVertex3f(0.5, 0.18, 0);
    glVertex3f(0.5, -0.18, 0);
    glVertex3f(0.17, 0.0, 0);
    glEnd();

    //top triangle
    glBegin(GL_POLYGON);
    glColor3f(0.0f / 255, 101.0f / 255, 191.0f / 255);
    glVertex3f(-0.38, 0.25, 0);
    glVertex3f(0.38, 0.25, 0);
    glVertex3f(0.0, 0.05, 0);
    glEnd();

    //bottom triangle
    glBegin(GL_POLYGON);
    glColor3f(0.0f / 255, 101.0f / 255, 191.0f / 255);
    glVertex3f(-0.38, -0.25, 0);
    glVertex3f(0.38, -0.25, 0);
    glVertex3f(0.0, -0.05, 0);
    glEnd();

    //outline
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f / 255, 101.0f / 255, 191.0f / 255);
    glVertex3f(-0.5, 0.25, 0);
    glVertex3f(0.5, 0.25, 0);
    glVertex3f(0.5, -0.25, 0);
    glVertex3f(-0.5, -0.25, 0);
    glEnd();
}

void drawJapanFlag()
{
    float x1 = 0.0, y1 = 0.0; // center
    float radius = 0.16;

    glBegin(GL_LINE_LOOP);
    glColor3f(255.0f / 255, 255.0f / 255, 255.0f / 255);
    glVertex3f(-0.5, 0.25, 0);
    glVertex3f(0.5, 0.25, 0);
    glVertex3f(0.5, -0.25, 0);
    glVertex3f(-0.5, -0.25, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);

    for (float angle = 0; angle <= 2 * M_PI; angle += 0.1)
    {
        glVertex2f(x1 + cos(angle) * radius, y1 + sin(angle) * radius);
    }

    glEnd();

    //outline
    glBegin(GL_LINE_LOOP);
    glColor3f(169.0f / 255, 169.0f / 255, 169.0f / 255);
    glVertex3f(-0.5, 0.25, 0);
    glVertex3f(0.5, 0.25, 0);
    glVertex3f(0.5, -0.25, 0);
    glVertex3f(-0.5, -0.25, 0);
    glEnd();
}

void drawAngryBird()
{
    // background texture
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);

    texture = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
        (
            "/home/liho/Desktop/graphic-programming/gp-practical-1/angry-bird-gb.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y);

    glBindTexture(GL_TEXTURE_2D, texture);
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

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    float radius = 0.0;

    // outer body
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(0.0f, 0.0f, -7.0f);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(254.0 / 255, 0.0 / 255, 54.0 / 255);
    for (float angle = degToRad(0); angle < degToRad(360); angle += 0.01)
    {
        glVertex2f(cos(angle) * 1.45, sin(angle) * 1.35);
    }
    glEnd();

    // inner body
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(0.0f, 0.0f, -7.0f);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(213.0 / 255, 0.0 / 255, 44.0 / 255);
    for (float angle = degToRad(0); angle < degToRad(360); angle += 0.01)
    {
        glVertex2f(cos(angle) * 1.35, sin(angle) * 1.25);
    }
    glEnd();

    // chest
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(0.0f, -1.0f, -7.0f);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(226.0 / 255, 196.0 / 255, 168.0 / 255);
    for (float angle = degToRad(0); angle < degToRad(360); angle += 0.01)
    {
        glVertex2f(cos(angle) * 0.9, sin(angle) * 0.33);
    }
    glEnd();

    // body outline
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(0.0f, 0.0f, -7.0f);
    glLineWidth(7.5);
    glBegin(GL_LINE_LOOP);
    glColor3f(5.0 / 255, 5.0 / 255, 5.0 / 255);
    for (float angle = degToRad(0); angle < degToRad(360); angle += 0.01)
    {
        glVertex2f(cos(angle) * 1.45, sin(angle) * 1.35);
    }
    glEnd();

    // back crown
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(-0.1f, 1.45f, -7.0f);
    glRotatef(-5.0f, 0.0f, 0.0f, 1.0);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(254.0 / 255, 0.0 / 255, 54.0 / 255);
    for (float angle = degToRad(0); angle < degToRad(360); angle += 0.01)
    {
        glVertex2f(cos(angle) * 0.6, sin(angle) * 0.18);
    }
    glEnd();
    glLineWidth(5);
    glBegin(GL_LINE_STRIP);
    glColor3f(5.0 / 255, 5.0 / 255, 5.0 / 255);
    for (float angle = degToRad(0); angle < degToRad(260); angle += 0.01)
    {
        glVertex2f(cos(angle) * 0.6, sin(angle) * 0.18);
    }
    glEnd();

    // inner crown
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(213.0 / 255, 0.0 / 255, 44.0 / 255);
    for (float angle = degToRad(0); angle < degToRad(360); angle += 0.01)
    {
        glVertex2f(cos(angle) * 0.33, sin(angle) * 0.1);
    }
    glEnd();

    // front crown
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(0.27f, 1.5f, -7.0f);
    glRotatef(-33.0f, 0.0f, 0.0f, 1.0);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(254.0 / 255, 0.0 / 255, 54.0 / 255);
    for (float angle = degToRad(0); angle < degToRad(360); angle += 0.01)
    {
        glVertex2f(cos(angle) * 0.55, sin(angle) * 0.22);
    }
    glEnd();
    glLineWidth(6.5);
    glBegin(GL_LINE_STRIP);
    glColor3f(5.0 / 255, 5.0 / 255, 5.0 / 255);
    for (float angle = degToRad(-15); angle < degToRad(275); angle += 0.01)
    {
        glVertex2f(cos(angle) * 0.55, sin(angle) * 0.22);
    }
    glEnd();

    // inner crown
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(213.0 / 255, 0.0 / 255, 44.0 / 255);
    for (float angle = degToRad(0); angle < degToRad(360); angle += 0.01)
    {
        glVertex2f(cos(angle) * 0.37, sin(angle) * 0.13);
    }
    glEnd();

    // tails
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(-1.45f, -0.15f, -7.0f);
    glBegin(GL_QUADS);
    glColor3f(5.0 / 255, 5.0 / 255, 5.0 / 255);
    glVertex2f(-0.12, 0.72);
    glVertex2f(0.0, 0.45);
    glVertex2f(0.0, 0.25);
    glVertex2f(-0.32, 0.57);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(5.0 / 255, 5.0 / 255, 5.0 / 255);
    glVertex2f(-0.45, 0.55);
    glVertex2f(0.0, 0.3);
    glVertex2f(0.0, 0.15);
    glVertex2f(-0.55, 0.25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(5.0 / 255, 5.0 / 255, 5.0 / 255);
    glVertex2f(-0.35, 0.13);
    glVertex2f(0.0, 0.17);
    glVertex2f(0.0, 0.1);
    glVertex2f(-0.3, -0.05);
    glEnd();

    // spots
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(-0.75f, -0.35f, -7.0f);
    glRotatef(-20.0f, -1.3f, 0.5f, -7.0);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(170.0 / 255, 0.0 / 255, 36.0 / 255);
    for (float angle = degToRad(0); angle < degToRad(360); angle += 0.01)
    {
        glVertex2f(cos(angle) * 0.13, sin(angle) * 0.17);
    }
    glEnd();

    // spots
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(-0.4f, -0.25f, -7.0f);
    glRotatef(-5.0f, -1.3f, 0.5f, -7.0);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(170.0 / 255, 0.0 / 255, 36.0 / 255);
    for (float angle = degToRad(0); angle < degToRad(360); angle += 0.01)
    {
        glVertex2f(cos(angle) * 0.13, sin(angle) * 0.25);
    }
    glEnd();

    // spots
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(0.15, -0.12f, -7.0f);
    glRotatef(30.0f, -1.3f, 0.5f, -7.0);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(170.0 / 255, 0.0 / 255, 36.0 / 255);
    for (float angle = degToRad(0); angle < degToRad(360); angle += 0.01)
    {
        glVertex2f(cos(angle) * 0.31, sin(angle) * 0.45);
    }
    glEnd();

    // spots
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(0.95, -0.08f, -7.0f);
    glRotatef(-30.0f, -1.3f, 0.5f, -7.0);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(170.0 / 255, 0.0 / 255, 36.0 / 255);
    for (float angle = degToRad(0); angle < degToRad(360); angle += 0.01)
    {
        glVertex2f(cos(angle) * 0.33, sin(angle) * 0.38);
    }
    glEnd();

    // left eye
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(0.3f, 0.0f, -7.0f);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(255.0 / 255, 255.0 / 255, 255.0 / 255);
    radius = 0.3;
    for (float angle = degToRad(0); angle < degToRad(360); angle += 0.01)
    {
        glVertex2f(cos(angle) * radius, sin(angle) * radius);
    }
    glEnd();
    glLineWidth(4.5);
    glBegin(GL_LINE_LOOP);
    glColor3f(5.0 / 255, 5.0 / 255, 5.0 / 255);
    radius = 0.3;
    for (float angle = degToRad(0); angle < degToRad(360); angle += 0.01)
    {
        glVertex2f(cos(angle) * radius, sin(angle) * radius);
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(5.0 / 255, 5.0 / 255, 5.0 / 255);
    radius = 0.105;
    for (float angle = degToRad(0); angle < degToRad(360); angle += 0.01)
    {
        glVertex2f(cos(angle) * radius, sin(angle) * radius);
    }
    glEnd();

    // right eye
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(0.9f, 0.0f, -7.0f);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(255.0 / 255, 255.0 / 255, 255.0 / 255);
    radius = 0.3;
    for (float angle = degToRad(0); angle < degToRad(360); angle += 0.01)
    {
        glVertex2f(cos(angle) * radius, sin(angle) * radius);
    }
    glEnd();
    glLineWidth(3.5);
    glBegin(GL_LINE_LOOP);
    glColor3f(5.0 / 255, 5.0 / 255, 5.0 / 255);
    radius = 0.3;
    for (float angle = degToRad(0); angle < degToRad(360); angle += 0.01)
    {
        glVertex2f(cos(angle) * radius, sin(angle) * radius);
    }
    glEnd();
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(0.78f, 0.0f, -7.0f);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(5.0 / 255, 5.0 / 255, 5.0 / 255);
    radius = 0.09;
    for (float angle = degToRad(0); angle < degToRad(360); angle += 0.01)
    {
        glVertex2f(cos(angle) * radius, sin(angle) * radius);
    }
    glEnd();

    //left eyebrown
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(0.35f, -0.07f, -7.0f);
    glBegin(GL_QUADS);
    glColor3f(5.0 / 255, 5.0 / 255, 5.0 / 255);
    glVertex2f(-0.5, 0.60);
    glVertex2f(0.25, 0.3);
    glVertex2f(0.25, 0.15);
    glVertex2f(-0.55, 0.35);
    glEnd();

    //right eyebrown
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(0.85f, -0.07f, -7.0f);
    glBegin(GL_QUADS);
    glColor3f(5.0 / 255, 5.0 / 255, 5.0 / 255);
    glVertex2f(-0.25, 0.3);
    glVertex2f(0.5, 0.60);
    glVertex2f(0.55, 0.35);
    glVertex2f(-0.25, 0.15);
    glEnd();

    //upper beak
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(0.6f, -0.5f, -7.0f);
    glBegin(GL_TRIANGLES);
    glColor3f(250.0 / 255, 185.0 / 255, 29.0 / 255);
    glVertex2f(0.0, 0.4);
    glVertex2f(0.7, -0.13);
    glVertex2f(-0.55, -0.05);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(5.0 / 255, 5.0 / 255, 5.0 / 255);
    glVertex2f(0.0, 0.4);
    glVertex2f(0.7, -0.13);
    glVertex2f(-0.55, -0.05);
    glEnd();

    //bottom beak
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(0.6f, -0.5f, -7.0f);
    glBegin(GL_TRIANGLES);
    glColor3f(245.0 / 255, 156.0 / 255, 30.0 / 255);
    glVertex2f(-0.05, -0.4);
    glVertex2f(0.4, -0.13);
    glVertex2f(-0.55, -0.05);
    glEnd();
    glLineWidth(4.5);
    glBegin(GL_LINE_LOOP);
    glColor3f(5.0 / 255, 5.0 / 255, 5.0 / 255);
    glVertex2f(-0.05, -0.4);
    glVertex2f(0.4, -0.13);
    glVertex2f(-0.55, -0.05);
    glEnd();
}

void drawFlags()
{
    glMatrixMode(GL_MODELVIEW); // To operate on model-view matrix

    glLineWidth(1.5);
    // pahang flag
    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(-3.0f, 0.0f, -7.0f);
    drawPahangFlag();

    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(-1.5f, 0.0f, -7.0f);
    drawNSFlag();

    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(0.0f, 0.0f, -7.0f);
    drawEnglandFlag();

    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(1.5f, 0.0f, -7.0f);
    drawScotlandFlag();

    glLoadIdentity(); // Reset the model-view matrix
    glTranslatef(3.0f, 0.0f, -7.0f);
    drawJapanFlag();
}
/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT); // Clear color buffers

    if (isDrawFlag)
    {
        drawFlags();
    }
    else
    {
        drawAngryBird();
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
    case GLUT_KEY_RIGHT:
        isDrawFlag = !isDrawFlag;
        break;
    case GLUT_KEY_LEFT:
        isDrawFlag = !isDrawFlag;
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
    default:
        break;
    }
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char **argv)
{
    glutInit(&argc, argv); // Initialize GLUT
    glutSetOption(GLUT_MULTISAMPLE, 16);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE); // Enable double buffered mode
    glutInitWindowSize(1920, 1080);                                               // Set the window's initial width & height
    glutInitWindowPosition(0, 0);                                                 // Position the window's initial top-left corner
    glutCreateWindow(title);                                                      // Create window with the given title

    init();

    glutDisplayFunc(display); // Register callback handler for window re-paint event
    glutReshapeFunc(reshape); // Register callback handler for window re-size event
    glutSpecialFunc(SpecialKeyHandler);
    glutKeyboardFunc(NormalKeyHandler);

    glutMainLoop(); // Enter the infinite event-processing loop
    return 0;
}