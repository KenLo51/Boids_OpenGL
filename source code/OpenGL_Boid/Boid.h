#ifndef BOID_CLASS_H
#define BOID_CLASS_H

#include <iostream>
#include <vector>
#include <random>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>

typedef struct {
	glm::vec3 position;
	glm::vec3 velocitie;
	glm::vec3 up;

	float baseSpeed;
	float speedRange;
} Bird;

class Boids {
public:
	unsigned int size;

	// boids
	std::vector<Bird> birds;

	// the neighbors that in range will effect rules
	float separationR;
	float alignmentR;
	float cohesionR;

	float separationMul = 0.4f;
	float alignmentMul = 0.01f;
	float cohesionMul = 0.1f;
	float barrierMul = 2.2f;

public:
	// Constructors
	Boids();
	Boids(unsigned int nBoids);
	Boids(unsigned int nBoids, float sr, float ar, float cr);
	// Destructor
	~Boids();

	// create boids
	void Init(unsigned int nBoids);
	// simulation by 3 rules
	void Step(float deltaTime);

};

#endif