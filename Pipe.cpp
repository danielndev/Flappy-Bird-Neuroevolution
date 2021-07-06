#include<iostream>;
#include <SDL.h>
#include "SDL2_gfxPrimitives.h"
#include "Pipe.h"


Pipe::Pipe(float x, float gapB, float gapSize) {
	Pipe::x = x;
	Pipe::gapBottom = gapB;
	Pipe::gapSize = gapSize;
}

void Pipe::draw(SDL_Renderer* renderer) {
	boxRGBA(renderer, x, 0, x + width, gapBottom - gapSize, 0, 255, 0, 255);
	boxRGBA(renderer, x, gapBottom, x + width, 1000, 0, 255, 0, 255);
	rectangleRGBA(renderer, x, -10, x + width, gapBottom - gapSize, 0, 0, 0, 255);
	rectangleRGBA(renderer, x, gapBottom, x + width, 1000, 0, 0, 0, 255);
}

void Pipe::logic() {
	x -= speed;
}

float Pipe::getX() {
	return x;
}

float Pipe::getWidth() {
	return width;
}

float Pipe::getGapSize() {
	return gapSize;
}

float Pipe::getGapBottom() {
	return gapBottom;
}

bool Pipe::getPassed() {
	return passed;
}

void Pipe::setPassed() {
	passed = true;
}