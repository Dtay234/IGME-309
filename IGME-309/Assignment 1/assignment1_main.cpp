#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>
using namespace std;

float canvasSize[] = { 10.0f, 10.0f };
int rasterSize[] = { 1000, 1000 };

int vertices = 20;

void drawFilledCircle(float red, float green, float blue, float center_x, float center_y, float radius);

void drawWireframeCircle(float red, float green, float blue, float center_x, float center_y, float radius, float lineWidth);



void display(void)
{
	glClearColor(1.0, 0.9, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	drawFilledCircle(1, 1, 1, 5, 4, 2.5);
	drawFilledCircle(1, 1, 1, 5, 7.5, 2);
	drawFilledCircle(0, 0, 0, 5, 7, 0.5);
	drawFilledCircle(0, 0, 0, 3.8, 5, 1);
	drawFilledCircle(0, 0, 0, 6.2, 5, 1);
	drawFilledCircle(0, 0, 0, 3.5, 2, 1.5);
	drawFilledCircle(0, 0, 0, 6.5, 2, 1.5);
	drawFilledCircle(0, 0, 0, 5.8, 8, 0.8);
	drawFilledCircle(0, 0, 0, 4.2, 8, 0.8);
	drawFilledCircle(1, 1, 1, 4.2, 8, 0.5);
	drawFilledCircle(1, 1, 1, 5.8, 8, 0.5);
	drawFilledCircle(0, 0, 0, 5.7, 8, 0.3);
	drawFilledCircle(0, 0, 0, 4.3, 8, 0.3);
	drawFilledCircle(0, 0, 0, 6, 9.5, 0.5);
	drawFilledCircle(0, 0, 0, 4, 9.5, 0.5);

	drawWireframeCircle(0, 1, 0, 5, 5, 6, 5);

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	rasterSize[0] = w;
	rasterSize[1] = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0f, canvasSize[0], 0.0f, canvasSize[1]);
	glViewport(0, 0, rasterSize[0], rasterSize[1]);

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
		break;
	case 43:
		if (vertices == 100) {
			return;
		}
		vertices++;
		display();
		break;
	case 45:
		if (vertices == 3) {
			return;
		}
		vertices--;
		display();
		break;
	}
	

}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(rasterSize[0], rasterSize[1]);
	glutCreateWindow("Assignment 1");

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;


}

void drawWireframeCircle(float red, float green, float blue, float center_x, float center_y, float radius, float lineWidth)
{
	glLineWidth(lineWidth);
	glBegin(GL_LINE_LOOP);
	glColor3f(red, green, blue);
	
	// loop around circle with changing angle and calculate coordinates
	for (size_t i = 0; i < vertices; i++)
	{
		float x = center_x + radius * cos(2 * M_PI * i / vertices);
		float y = center_y + radius * sin(2 * M_PI * i / vertices);
		float temp[2] = { x, y };
		glVertex2fv(temp);

	}

	glEnd();

}

void drawFilledCircle(float red, float green, float blue, float center_x, float center_y, float radius)
{
	
	glBegin(GL_POLYGON);
	glColor3f(red, green, blue);
	
	// loop around circle with changing angle and calculate coordinates
	for (size_t i = 0; i < vertices; i++)
	{
		float x = center_x + radius * cos(2 * M_PI * i / vertices);
		float y = center_y + radius * sin(2 * M_PI * i / vertices);
		float temp[2] = { x, y };
		glVertex2fv(temp);
		
	}

	glEnd();
}


