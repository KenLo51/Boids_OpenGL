#include "Boid.h"

// Constructors
Boids::Boids() {
	size = 0;
	separationR = 1.0f;
	alignmentR = 1.0f;
	cohesionR = 1.0f;
}
Boids::Boids(unsigned int nBoids) {
	Init(nBoids);

	separationR = 1.0f;
	alignmentR = 1.0f;
	cohesionR = 1.0f;
}
Boids::Boids(unsigned int nBoids, float sr, float ar, float cr) {
	Init(nBoids);

	separationR = sr;
	alignmentR = ar;
	cohesionR = cr;
}
// Destructor
Boids::~Boids() {
	birds.clear();
}

// create boids
void Boids::Init(unsigned int nBoids) {
	size = nBoids;
	birds.resize(nBoids);

	for (unsigned int i = 0; i < nBoids; i++) {
		birds[i].position = glm::linearRand(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		birds[i].velocitie = glm::normalize(glm::ballRand(1.0f)) * 0.5f;
		birds[i].baseSpeed = 0.4f;
		birds[i].speedRange = 0.1f;
	}
}
// simulation by 3 rules
void Boids::Step(float deltaTime) {
	for (unsigned int i = 0; i < size; i++) {
		Bird& curr = birds[i];

		// Separation
		glm::vec3 sVec = glm::vec3(0.0f, 0.0f, 0.0f);
		unsigned int sn = 0;
		for (unsigned int j = 0; j < birds.size(); j++) {
			if (i == j) continue; // boid itself
			Bird& neighbor = birds[j];

			// check if neighbor is too far
			if (glm::length(curr.position - neighbor.position) > separationR) continue;

			//
			sVec += glm::normalize(curr.position - neighbor.position) * (separationR- glm::length(curr.position - neighbor.position)) / separationR;
			sn += 1;
		}
		if (sn) sVec = sVec / (float)sn;

		// Alignment
		glm::vec3 aVec = glm::vec3(0.0f, 0.0f, 0.0f);
		unsigned int an = 0;
		for (unsigned int j = 0; j < size; j++) {
			if (i == j) continue; // boid itself
			Bird& neighbor = birds[j];

			// check if neighbor is too far
			if (glm::length(curr.position - neighbor.position) > alignmentR) continue;

			aVec += neighbor.velocitie - curr.velocitie;
			sn += 1;
		}
		if(an) aVec = aVec / (float)an;

		// Cohesion
		glm::vec3 cVel = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 cPos = curr.position;
		unsigned int cn = 1;
		for (unsigned int j = 0; j < size; j++) {
			if (i == j) continue; // boid itself
			Bird& neighbor = birds[j];

			// check if neighbor is too far
			if (glm::length(curr.position - neighbor.position) > cohesionR) continue;
			cPos += neighbor.position;
			cn += 1;
		}
		cPos = (cPos / (float)cn);
		cVel = cPos - curr.position;

		// Barrier
		glm::vec3 bVec = glm::vec3(0.0f, 0.0f, 0.0f);
		if (curr.position.x > 0.9) bVec.x = 0.9 - curr.position.x;
		if (curr.position.x < -0.9) bVec.x = -0.9 - curr.position.x;
		if (curr.position.y > 0.9) bVec.y = 0.9 - curr.position.y;
		if (curr.position.y < -0.9) bVec.y = -0.9 - curr.position.y;
		if (curr.position.z > 0.9) bVec.z = 0.9 - curr.position.z;
		if (curr.position.z < -0.9) bVec.z = -0.9 - curr.position.z;

		// sum
		glm::vec3 totalVec = separationMul * sVec + alignmentMul * aVec + cohesionMul * cVel + barrierMul * bVec;
		curr.velocitie += 0.1f * totalVec;
		curr.velocitie += 0.1f * (curr.baseSpeed - glm::length(curr.velocitie));
		if (glm::length(curr.velocitie) > (curr.baseSpeed + curr.speedRange))
			curr.velocitie = glm::normalize(curr.velocitie) * (curr.baseSpeed + curr.speedRange);
		if (glm::length(curr.velocitie) < (curr.baseSpeed - curr.speedRange))
			curr.velocitie = glm::normalize(curr.velocitie) * (curr.baseSpeed - curr.speedRange);

		// update boid
		curr.position += deltaTime * curr.velocitie;
		//if (curr.position.x > 1.0f) curr.position.x = 1.0f;
		//if (curr.position.x < -1.0f) curr.position.x = -1.0f;
		//if (curr.position.y > 1.0f) curr.position.y = 1.0f;
		//if (curr.position.y < -1.0f) curr.position.y = -1.0f;
		//if (curr.position.z > 1.0f) curr.position.z = 1.0f;
		//if (curr.position.z < -1.0f) curr.position.z = -1.0f;
	}
}