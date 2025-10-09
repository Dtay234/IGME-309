#include "MyMesh.h"
#include <GL/freeglut.h>

#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
using namespace std;

MyMesh::MyMesh()
{
	vertNum = triNum = 0;
	vertices = NULL;
	indices = NULL;
	vertColors = NULL;
}

MyMesh::~MyMesh()
{
	if (vertices != NULL)
		delete[] vertices;
	if (indices != NULL)
		delete[] indices;

	if (vertColors != NULL)
		delete[] vertColors;
}

void MyMesh::load(char* fileName)
{
	vertNum = 0;
	triNum = 0;

	vertices = new float[100 * 2];
	indices = new unsigned int[100 * 3];
	vertColors = new float[100 * 3];

	ifstream file(fileName);

	if (!file.is_open())
	{
		/****************************************/
		// Write your code below

		std::cerr << "File could not be opened" << std::endl;
		return; // Or handle the error appropriately


		// Write your code above
		/****************************************/
	}

	/****************************************/
	// Write your code below

	string str;

	auto stringsplit = [](string str, char delimiter) {
		int splits = 1;
		for (size_t i = 0; i < str.length(); i++)
		{
			if (str[i] == delimiter) {
				splits++;
			}
		}

		string* splitString = new string[splits];
		string current = "";
		splits = 0;

		for (size_t i = 0; i < str.length(); i++)
		{
			if (str[i] != delimiter) {
				current += str[i];
			}
			else {
				splitString[splits] = current;
				current = "";
				splits++;
			}
		}

		splitString[splits] = current;

		return splitString;
		};

	while (std::getline(file, str)) {
		if (str[0] == 'v') {
			string* split = stringsplit(str, ' ');
			vertices[vertNum * 2] = std::stof(split[1]);
			vertices[vertNum * 2 + 1] = std::stof(split[2]);
			// std::cout << "(" << vertices[vertNum * 2 + 0] << ", " << vertices[vertNum * 2 + 1] << ")" << endl;
			++vertNum;

			delete[] split;
		}
		else if (str[0] == 'f') {
			string* split = stringsplit(str, ' ');
			indices[triNum * 3] = std::stoi(split[1]) - 1;
			indices[triNum * 3 + 1] = std::stoi(split[2]) - 1;
			indices[triNum * 3 + 2] = std::stoi(split[3]) - 1;
			// std::cout << "index 1: " << indices[triNum * 3 + 0] << endl;
			// std::cout << "index 2: " << indices[triNum * 3 + 1] << endl;
			// std::cout << "index 3: " << indices[triNum * 3 + 2] << endl;
			++triNum;

			delete[] split;
		}
	}

	file.close();

	// Write your code above
	/****************************************/

	// generate random vertex colors
	for (unsigned int i = 0; i < vertNum; i++)
	{
		vertColors[i * 3 + 0] = float(rand()) / (RAND_MAX + 1);
		vertColors[i * 3 + 1] = float(rand()) / (RAND_MAX + 1);
		vertColors[i * 3 + 2] = float(rand()) / (RAND_MAX + 1);
	}

	// cout << *(vertices + indices[0 * 3 + 0] * 2) << endl;
	// cout << *(vertices + indices[0 * 3 + 1] * 2) << endl;
}

void MyMesh::load(const unsigned int p_vertNum, const unsigned int p_triNum, const float* p_vertices, const unsigned int* p_indices)
{
	vertNum = p_vertNum;
	triNum = p_triNum;

	vertices = new float[vertNum * 2];
	indices = new unsigned int[triNum * 3];
	vertColors = new float[vertNum * 3];

	for (unsigned int i = 0; i < vertNum * 2; i++)
	{
		vertices[i] = p_vertices[i];
	}

	for (unsigned int i = 0; i < triNum * 3; i++)
	{
		indices[i] = p_indices[i];
	}

	// generate random vertex colors
	for (unsigned int i = 0; i < vertNum; i++)
	{
		vertColors[i * 3 + 0] = float(rand()) / (RAND_MAX + 1);
		vertColors[i * 3 + 1] = float(rand()) / (RAND_MAX + 1);
		vertColors[i * 3 + 2] = float(rand()) / (RAND_MAX + 1);
	}
}

void MyMesh::update()
{
	// we will use this for transformations later....
}

void MyMesh::draw()
{
	for (int i = 0; i < triNum; ++i)
	{
		glBegin(GL_TRIANGLES);
		glColor3fv(vertColors + indices[i * 3 + 0] * 3);
		glVertex2fv(vertices + indices[i * 3 + 0] * 2);

		glColor3fv(vertColors + indices[i * 3 + 1] * 3);
		glVertex2fv(vertices + indices[i * 3 + 1] * 2);

		glColor3fv(vertColors + indices[i * 3 + 2] * 3);
		glVertex2fv(vertices + indices[i * 3 + 2] * 2);
		glEnd();
	}
}