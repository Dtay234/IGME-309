#pragma once
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <vector>

using namespace std;

class PolyObject
{
private:
    vector<float> vertices; // all vertices in C++ vector
    float *color;    // color of this polygon
public:
    PolyObject();
    ~PolyObject();
    void addVertex(float x, float y);            // add vertex at the end of the vertex list
    void setColor(float cr, float cg, float cb); // set the color of this polygon
    unsigned int getVertNum();                   // return the number of vertices
    void draw();                                 // draw the polygon if it’s completed
};