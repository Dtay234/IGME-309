//Usage:
//Hold down the number keys , 1-7, to select one or multiple circles.
//While circle(s) are selected, use the left mouse button to translate and use the right mouse button to rotate.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include <math.h>
using namespace std;

#define MAX_NUM_CIRCLE 16
#define CIRCLE_RADIUM 2.0

int win_width = 600, win_height = 600;
float canvas_width = 20.0f; float canvas_height = 20.0f;

int selectedID = 0;


bool keyStates[256];
int buttonState;
float colors[3*MAX_NUM_CIRCLE];
float translations[2*MAX_NUM_CIRCLE];
float rotations[MAX_NUM_CIRCLE];

float curMouse[2];
float preMouse[2];

void init(void)
{
    for(int i = 0; i<256; i++) {
        keyStates[i] = false;
    }
    for(int i=0; i<MAX_NUM_CIRCLE; i++) {
        colors[i*3+0] = 0.0f; // red
        colors[i*3+1] = 0.0f; // green
        colors[i*3+2] = 0.0f; // blue
        
        translations[i*2+0] = 0.0f; // x
        translations[i*2+1] = 0.0f; // y
        
        rotations[i] = 0.0f;
    }

    colors[selectedID * 3 + 0] = 0;
    colors[selectedID * 3 + 1] = 1;
    colors[selectedID * 3 + 2] = 0;
    
    buttonState = -1;
}

void drawCircle(float radius, const float* c)
{
    glColor3fv(c);
    glLineWidth(3.0f);
    glBegin(GL_LINE_STRIP);
    for(int i=0; i<=100; i++)
        glVertex2f(radius*cosf(3.14*2/100*i), radius*sinf(3.14*2/100*i));
    glEnd();
}

void display(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    int id = 0;

    glRotatef(rotations[id], 0, 0, 1);
    drawCircle(1.5 , colors + id * 3);
    glPushMatrix();
    glPushMatrix();

    id = 1;
    glTranslatef(0, 2.5, 0);
    glRotatef(rotations[id], 0, 0, 1);
    glPushMatrix();
    glPushMatrix();
    drawCircle(2 , colors + id * 3);

    id = 2;
    glTranslatef(0, 2, 0);
    glRotatef(rotations[id], 0, 0, 1);
    drawCircle(1 , colors + id * 3);

    id = 3;
    glTranslatef(0, 1.5, 0);
    glRotatef(rotations[id], 0, 0, 1);
    drawCircle(1.5 , colors + id * 3);

    glPopMatrix();
    id = 4;
    glTranslatef(-2.5, 0, 0);
    glRotatef(rotations[id], 0, 0, 1);
    drawCircle(1, colors + id * 3);

    id = 5;
    glTranslatef(-1.5, 0, 0);
    glRotatef(rotations[id], 0, 0, 1);
    drawCircle(1, colors + id * 3);

    id = 6;
    glTranslatef(-1.5, 0, 0);
    glRotatef(rotations[id], 0, 0, 1);
    drawCircle(1.5, colors + id * 3);

    glPopMatrix();
    id = 7;
    glTranslatef(2.5, 0, 0);
    glRotatef(rotations[id], 0, 0, 1);
    drawCircle(1, colors + id * 3);

    id = 8;
    glTranslatef(1.5, 0, 0);
    glRotatef(rotations[id], 0, 0, 1);
    drawCircle(1, colors + id * 3);

    id = 9;
    glTranslatef(1.5, 0, 0);
    glRotatef(rotations[id], 0, 0, 1);
    drawCircle(1.5, colors + id * 3);

    glPopMatrix();
    id = 10;
    glTranslatef(1, -1, 0);
    glRotatef(rotations[id], 0, 0, 1);
    drawCircle(1.2, colors + id * 3);

    id = 11;
    glTranslatef(0, -2, 0);
    glRotatef(rotations[id], 0, 0, 1);
    drawCircle(1.2, colors + id * 3);

    id = 12;
    glTranslatef(0, -2, 0);
    glRotatef(rotations[id], 0, 0, 1);
    drawCircle(1.5, colors + id * 3);

    glPopMatrix();
    id = 13;
    glTranslatef(-1, -1, 0);
    glRotatef(rotations[id], 0, 0, 1);
    drawCircle(1.2, colors + id * 3);

    id = 14;
    glTranslatef(0, -2, 0);
    glRotatef(rotations[id], 0, 0, 1);
    drawCircle(1.2, colors + id * 3);

    id = 15;
    glTranslatef(0, -2, 0);
    glRotatef(rotations[id], 0, 0, 1);
    drawCircle(1.5, colors + id * 3);

    /*
    // the following codes could be written in a for loop.
    // Here I expand them so that you can better trace the changes of cirlce's coordinate system.
    
    int cid = -1; // the index of current circle
    // circle 0
    cid = 0;
    glTranslatef(translations[cid*2+0], translations[cid*2+1], 0.0f);
    glRotatef(rotations[cid], 0.0f, 0.0f, 1.0f);
    drawCircle(CIRCLE_RADIUM * (MAX_NUM_CIRCLE-cid)/MAX_NUM_CIRCLE, colors+cid*3);
    
    // circle 1
    cid = 1;
    glTranslatef(translations[cid*2+0], translations[cid*2+1], 0.0f);
    glRotatef(rotations[cid], 0.0f, 0.0f, 1.0f);
    glPushMatrix(); // push the circle 1's CS to the modelview stack
    drawCircle(CIRCLE_RADIUM * (MAX_NUM_CIRCLE-cid)/MAX_NUM_CIRCLE, colors+cid*3);
    
    // circle 2
    cid = 2;
    glTranslatef(translations[cid*2+0], translations[cid*2+1], 0.0f);
    glRotatef(rotations[cid], 0.0f, 0.0f, 1.0f);
    drawCircle(CIRCLE_RADIUM * (MAX_NUM_CIRCLE-cid)/MAX_NUM_CIRCLE, colors+cid*3);
    
    // circle 3
    cid = 3;
    glTranslatef(translations[cid*2+0], translations[cid*2+1], 0.0f);
    glRotatef(rotations[cid], 0.0f, 0.0f, 1.0f);
    drawCircle(CIRCLE_RADIUM * (MAX_NUM_CIRCLE-cid)/MAX_NUM_CIRCLE, colors+cid*3);
    
    
    glPopMatrix(); // back to the CS of Circle 1
    // circle 4
    cid = 4;
    glTranslatef(translations[cid*2+0], translations[cid*2+1], 0.0f);
    glRotatef(rotations[cid], 0.0f, 0.0f, 1.0f);
    drawCircle(CIRCLE_RADIUM * (MAX_NUM_CIRCLE-cid)/MAX_NUM_CIRCLE, colors+cid*3);
    
    // circle 5
    cid =5;
    glTranslatef(translations[cid*2+0], translations[cid*2+1], 0.0f);
    glRotatef(rotations[cid], 0.0f, 0.0f, 1.0f);
    drawCircle(CIRCLE_RADIUM * (MAX_NUM_CIRCLE-cid)/MAX_NUM_CIRCLE, colors+cid*3);
    */
    
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    win_width =  w;
    win_height = h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-canvas_width/2.0f, canvas_width/2.0f, -canvas_height/2.0f, canvas_height/2.0f);
    glViewport(0, 0, (GLsizei) win_width, (GLsizei) win_height);
    
    glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
    if (key == 27) // 'esc' key
        exit(0);
    
    //cout << key << endl;

    unsigned char asciiOffset = 49; // see an ascii table
    if (key == 97) {
        rotations[selectedID] += 5;
    }
    if (key == 100) {
        rotations[selectedID] -= 5;
    }

    if (key == 44 && selectedID > 0) {
        colors[selectedID * 3 + 0] = 0;
        colors[selectedID * 3 + 1] = 0;
        colors[selectedID * 3 + 2] = 0;
        selectedID -= 1;
        colors[selectedID * 3 + 0] = 0;
        colors[selectedID * 3 + 1] = 1;
        colors[selectedID * 3 + 2] = 0;
    }
    if (key == 46 && selectedID < 15) {
        colors[selectedID * 3 + 0] = 0;
        colors[selectedID * 3 + 1] = 0;
        colors[selectedID * 3 + 2] = 0;
        selectedID += 1;
        colors[selectedID * 3 + 0] = 0;
        colors[selectedID * 3 + 1] = 1;
        colors[selectedID * 3 + 2] = 0;
    }
    glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y)
{
    
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    
}

void motion(int x, int y)
{
    
    
}

int main(int argc, char *argv[])
{
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(win_width, win_height);
    glutCreateWindow("2D Transformation Tree");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();
    return 0;
    
}
