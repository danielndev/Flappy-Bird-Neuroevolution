#include <SDL.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "SDL2_gfxPrimitives.h"
#include "Pipe.h"
#include "Bird.h"

Bird::Bird(float x, float y) {

	Bird::x = x;
	Bird::y = y;

	Bird::startTime = time(NULL);
	col[0] = rand() % 255;
	col[1] = rand() % 255;
	col[2] = rand() % 255;

}

void Bird::draw(SDL_Renderer* renderer) {
	filledCircleRGBA(renderer, x, y, size, col[0], col[1], col[2], 200);
}

void Bird::logic(Pipe closestPipe) {
	vy += gravity;
	y += vy;

	//Think whether to jump

	float shouldJump = brain.findOutputs({ 
		y,
		closestPipe.getX(),
		closestPipe.getGapBottom()
		})[0];

	if (shouldJump > 0.5) {
		jump();
	}

	//Check collision
	if (x + size > closestPipe.getX() && x - size < closestPipe.getX() + closestPipe.getWidth() && (y - size < closestPipe.getGapBottom() - closestPipe.getGapSize() || y + size > closestPipe.getGapBottom())) {
		die();
	}

	if (y + size > 800) {
		die();
	}
}

void Bird::die() {
	alive = false;
	fitness = score * 1000 + time(NULL) - startTime;
}

void Bird::jump() {
	vy = -jumpStrength;
}

bool Bird::getAlive() {
	return alive;
}

void Bird::increaseScore() {
	score++;
}

int Bird::getScore() {
	return score;
}

void Bird::setSelectionProbability(float prob) {
	selectionProbability = prob;
}

float Bird::getSelectionProbability() {
	return selectionProbability;
}

void Bird::cloneBrain(Bird b) {
	brain = b.getBrain();
}

NeuralNetwork Bird::getBrain() {
	return brain;
}

void Bird::setBrain(NeuralNetwork b) {
	brain = b;
}

void Bird::mutate() {
	brain = brain.mutate();
}

float Bird::getFitness() {
	return fitness;
}