#include <GL/glew.h>
#include <GL/freeglut.h>
#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem(int _numParticles)
{
	numParticles = _numParticles;	// Set the number of particles
	
	// Allocate memory for positions, velocities, colors, and lifetimes.
	positions = new float[numParticles * 3];
	velocities = new float[numParticles * 3];
	colors = new float[numParticles * 4];	
	lifeTimes = new float[numParticles];

	for (int i = 0; i < numParticles; i++) {
		// Initialize the life times
		lifeTimes[i] = maxLifeTime - maxLifeTime * i / numParticles;

		/***************************/
		// Write your code below
		// Please add initializations for other arrays as you see appropriate.

		//initialize all values
		positions[i * 3 + 0] = 0;
		positions[i * 3 + 1] = 0;
		positions[i * 3 + 2] = 0;
		velocities[i * 3 + 0] = getRandomValue(minSpeedX, maxSpeedX);
		velocities[i * 3 + 1] = getRandomValue(minSpeedY, maxSpeedY);
		velocities[i * 3 + 2] = getRandomValue(minSpeedZ, maxSpeedZ);
		colors[i * 4 + 0] = getRandomValue(0, 1);
		colors[i * 4 + 1] = getRandomValue(0, 1);
		colors[i * 4 + 2] = getRandomValue(0, 1);
		colors[i * 4 + 3] = 256;
		
		
		/***************************/
	}
}

void ParticleSystem::update(float deltaTime)
{
	deltaTime /= 1000.0;
	for (int i = 0; i < numParticles; i++) {
		/***************************/
		// Write your code below
		// Update lifetime, velocity, position, and color.
		// Reset particle states (positions, velocities, colors, and lifetimes) when the lifetime reaches the maxLifeTime

		for (size_t i = 0; i < numParticles; i++)
		{
			lifeTimes[i] -= deltaTime;
			
			//update velocities
			velocities[i * 3 + 0] += acceleration[0] * deltaTime;
			velocities[i * 3 + 1] += acceleration[1] * deltaTime;
			velocities[i * 3 + 2] += acceleration[2] * deltaTime;

			//update positions
			positions[i * 3 + 0] += velocities[i * 3 + 0] * deltaTime;
			positions[i * 3 + 1] += velocities[i * 3 + 1] * deltaTime;
			positions[i * 3 + 2] += velocities[i * 3 + 2] * deltaTime;

			//decrease alpha with lifetime
			colors[i * 4 + 3] = lifeTimes[i] / maxLifeTime;

			//reset particle if it is past lifetime
			if (lifeTimes[i] <= 0) {
				lifeTimes[i] = maxLifeTime - maxLifeTime * i / numParticles;				
				positions[i * 3 + 0] = 0;
				positions[i * 3 + 1] = 0;
				positions[i * 3 + 2] = 0;
				velocities[i * 3 + 0] = getRandomValue(minSpeedX, maxSpeedX);
				velocities[i * 3 + 1] = getRandomValue(minSpeedY, maxSpeedY);
				velocities[i * 3 + 2] = getRandomValue(minSpeedZ, maxSpeedZ);
				colors[i * 4 + 0] = getRandomValue(0, 1);
				colors[i * 4 + 1] = getRandomValue(0, 1);
				colors[i * 4 + 2] = getRandomValue(0, 1);
				colors[i * 4 + 3] = 1;
			}
		}
		
		// Write your code above
		/***************************/
	}
}

void ParticleSystem::draw()
{
	/***************************/
	// Write your code below
	// Use GL_POINTS for rendering
	
	//draw each point
	glPointSize(5.0);
	glBegin(GL_POINTS);
	for (size_t i = 0; i < numParticles; i++)
	{
		glColor4fv(colors + i * 4);
		glVertex3fv(positions + i * 3);
		
	}
	glEnd();
	
	
	// Write your code above
	/***************************/
}

float ParticleSystem::getRandomValue(float min_value, float max_value)
{
	return min_value + (std::rand()) / (RAND_MAX / (max_value - min_value));;
}
