
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include "PolyObject.h";
#include <iostream>
using namespace std;

float canvasSize[] = {10.0f, 10.0f};
int rasterSize[] = {800, 600};

// structure for storing 3 2D vertices of a triangle
vector<int*> indices = vector<int*>();
vector<PolyObject*> polygons = vector<PolyObject*>();
int numOfVertices = 0;
float *v = new float[2*3];
float color[3];

float mousePos[2];

void init(void)
{
    for(int i=0; i<6; i++)
        v[i] = 0.0f;
    mousePos[0] = mousePos[1] = 0.0f;
    color[0] =1.0f;
    color[1] = color[2] = 0.0f;
    indices.push_back(new int[3] {0, 0, 0});
}

void drawCursor()
{
    glColor3f(1.0f, 0.0f, 1.0f);
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glVertex2fv(mousePos);
    glEnd();
    glPointSize(1.0f);
}

void display(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // draw every polygon
    for (size_t i = 0; i < polygons.size(); i++)
    {
        polygons[i]->draw();
    }

    glColor3fv(color);
    
    // if number of vertices is low, draw lines
    if(numOfVertices> 0 && numOfVertices<3) {
        
        glBegin(GL_LINE_STRIP);
        for(int i=0; i<numOfVertices; i++)
            glVertex2fv(v+i*2);
        glVertex2fv(mousePos);
        glEnd();
    }
    else if (numOfVertices >= 3) {
        //draw each triangle
        for (int i = 0; i < indices.size(); i++) {
            glBegin(GL_TRIANGLES);
            glVertex2fv(v + indices[i][0] * 2);
            glVertex2fv(v + indices[i][1] * 2);
            glVertex2fv(v + indices[i][2] * 2);
        }
        glEnd();
    }
    
    
    drawCursor();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    rasterSize[0] = w;
    rasterSize[1] = h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, canvasSize[0], 0.0, canvasSize[1]);
    glViewport(0, 0, rasterSize[0], rasterSize[1]);
    
    glutPostRedisplay();
}

void mouse (int button, int state, int x, int y)
{
    mousePos[0] = (float)x / rasterSize[0] * canvasSize[0];
    mousePos[1] = (float)(rasterSize[1] - y) / rasterSize[1] * canvasSize[1];
        
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        //resize array
        float* newV = new float[2 * (numOfVertices + 2)];

        //copy over
        for (size_t i = 0; i < 2 * (numOfVertices + 1); i++)
        {
            newV[i] = v[i];
        }

        //fill new spots
        newV[(numOfVertices) * 2 + 0] = mousePos[0];
        newV[(numOfVertices) * 2 + 1] = mousePos[1];
        newV[(numOfVertices + 1) * 2 + 0] = mousePos[0];
        newV[(numOfVertices + 1) * 2 + 1] = mousePos[1];

        //add new tri if there are enough vertices
        if (numOfVertices >= 2) {
            indices.push_back(new int[3] { 0, numOfVertices - 1, numOfVertices});
            indices[0][1] = numOfVertices;
            indices[0][2] = numOfVertices + 1;
        }
            

        numOfVertices++;

        //cleanup
        delete[] v;
        v = newV;

        
    }
    glutPostRedisplay();
}

void motion(int x, int y)
{
    // mouse events are handled by OS, eventually. When using mouse in the raster window, it assumes top-left is the origin.
    // Note: the raster window created by GLUT assumes bottom-left is the origin.
    mousePos[0] = (float)x / rasterSize[0] * canvasSize[0];
    mousePos[1] = (float)(rasterSize[1] - y) / rasterSize[1] * canvasSize[1];

    //dynamically show new shape
    v[numOfVertices * 2 + 0] = mousePos[0];
    v[numOfVertices * 2 + 1] = mousePos[1];
    
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key){
        case 27:
            exit(0);
            break;
        case 13:
            //save shape and reset 
            PolyObject* obj = new PolyObject();
            
            for (size_t i = 0; i < numOfVertices; i++)
            {
                obj->addVertex(v[i * 2 + 0], v[i * 2 + 1]);
                obj->setColor(color[0], color[1], color[2]);
            }

            polygons.push_back(obj);

            delete[] v;
            v = new float[2 * 3];

            for (size_t i = 0; i < indices.size(); i++)
            {
                delete[] indices[i];
            }
            indices.clear();

            numOfVertices = 0;

            for (int i = 0; i < 6; i++)
                v[i] = 0.0f;
            mousePos[0] = mousePos[1] = 0.0f;
            indices.push_back(new int[3] {0, 0, 0});

            break;
    }
}

void menu(int value)
{
    switch (value) {
        case 0: // clear
            numOfVertices = 0;
            glutPostRedisplay();
            break;
        case 1: //exit
            exit(0);
        case 2: // red
            color[0] = 1.0f;
            color[1] = 0.0f;
            color[2] = 0.0f;
            glutPostRedisplay();
            break;
        case 3: // green
            color[0] = 0.0f;
            color[1] = 1.0f;
            color[2] = 0.0f;
            glutPostRedisplay();
            break;
        case 4: // blue
            color[0] = 0.0f;
            color[1] = 0.0f;
            color[2] = 1.0f;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}
void createMenu()
{
    int colorMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Red", 2);
    glutAddMenuEntry("Green", 3);
    glutAddMenuEntry("Blue", 4);
    
    glutCreateMenu(menu);
    glutAddMenuEntry("Clear", 0);
    glutAddSubMenu("Colors", colorMenu);
    glutAddMenuEntry("Exit", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char *argv[])
{
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(rasterSize[0], rasterSize[1]);
    glutCreateWindow("Mouse Event - draw a triangle");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(motion);
    createMenu();
    glutMainLoop();

    //cleanup
    for (size_t i = 0; i < indices.size(); i++)
    {
        delete[] indices[i];
    }
    for (size_t i = 0; i < polygons.size(); i++)
    {
        delete polygons[i];
    }

    return 0;
    
    
}