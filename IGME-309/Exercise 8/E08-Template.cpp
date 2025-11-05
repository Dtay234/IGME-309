#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#define _USE_MATH_DEFINES

#include <ctime>
#include <cmath>

using namespace std;

float canvasSize[] = { 20.0f, 20.0f };
int rasterSize[] = { 600, 600 };

// tracking the game time - millisecond 
unsigned int curTime = 0;
unsigned int preTime = 0;
float deltaTime = 0;

float rotationAngle = 0.0f;
float rotateSpeed = 90.0f;

void display(void)
{
	glClearColor(0.9f, 0.9f, 0.7f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	
	/*****************************/
	// write your code below

	glTranslatef(10, 15, 0);
	glRotatef(rotationAngle, 0, 0, 1);
	glTranslatef(-10, -15, 0);

	glPointSize(5);
	glBegin(GL_POINTS);
	
	glColor3f(1, 0, 0);
	glVertex2f(10, 15);
	glEnd();

	glBegin(GL_LINES);

	glVertex2f(10, 15);
	glVertex2f(10, 5);
	glEnd();

	glBegin(GL_POLYGON);
	for (size_t i = 0; i < 36; i++)
	{
		float x = 10 + 1 * cos(i * 2 * M_PI / 36.0);
		float y = 5 + 1 * sin(2 * M_PI - (i * 2 * M_PI / 36.0));
		glVertex2f(x, y);

	}
	glEnd();

	

	// write your code above
	/*****************************/

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	rasterSize[0] = w;
	rasterSize[1] = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, canvasSize[0], 0, canvasSize[1]);
	glViewport(0, 0, rasterSize[0], rasterSize[1]);

	glutPostRedisplay();
}


void update() {
	curTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (float)(curTime - preTime) / 1000.0f; 


	if (rotationAngle > 45.0f) {
		rotateSpeed = -abs(rotateSpeed);
	}
	else if (rotationAngle < -45.0f) {
		rotateSpeed = abs(rotateSpeed);
	}
	rotationAngle += deltaTime * rotateSpeed;

	preTime = curTime;
	glutPostRedisplay();
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(rasterSize[0], rasterSize[1]);
	glutCreateWindow("Simple Pendulum");

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(update);
	
	preTime = glutGet(GLUT_ELAPSED_TIME);
	glutMainLoop();
	return 0;
}