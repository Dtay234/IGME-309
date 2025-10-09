#include "PolyObject.h"

PolyObject::PolyObject()
{
	vertices = vector<float>();
	color = new float[3];
}

PolyObject::~PolyObject()
{
	delete[] color;
}

void PolyObject::addVertex(float x, float y)
{
	vertices.push_back(x);
	vertices.push_back(y);
}

void PolyObject::setColor(float cr, float cg, float cb)
{
	color[0] = cr;
	color[1] = cg;
	color[2] = cb;
}

unsigned int PolyObject::getVertNum()
{
	// divide size of vector to get number of vertices
	return vertices.size() / 2;
}

void PolyObject::draw()
{
	
	
	// draw points, lines, and polygons
	switch (getVertNum()) {
		case 1:
			glBegin(GL_POINTS);
			glColor3fv(color);
			for (size_t i = 0; i < getVertNum(); i++)
			{
				glVertex2f(vertices[i * 2], vertices[i * 2 + 1]);
			}
			glEnd();
			break;
		case 2:
			glBegin(GL_LINES);
			glColor3fv(color);
			for (size_t i = 0; i < getVertNum(); i++)
			{
				glVertex2f(vertices[i * 2], vertices[i * 2 + 1]);
			}
			glEnd();

		default:
			glBegin(GL_POLYGON);
			glColor3fv(color);
			for (size_t i = 0; i < getVertNum(); i++)
			{
				glVertex2f(vertices[i * 2], vertices[i * 2 + 1]);
			}
			glEnd();
			break;
	}

	

	
}
