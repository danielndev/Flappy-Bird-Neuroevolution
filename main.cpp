#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include "SDL2_gfxPrimitives.h"
#include <vector>
#include "Pipe.h"
#include "Bird.h"

int w = 600;
int h = 800;
int birdX = w / 8;


std::vector<Bird> evolvePopulation(std::vector<Bird> birds);

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "STL could not initialise! SDL Error " << SDL_GetError() << std::endl;
	}

	int fps = 60;

	SDL_Window* window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	srand(static_cast <unsigned> (time(0)));

	float gapSize = 150;
	float gapBetweenPipes = 3 * w / 4;

	int maxPipeGap = h - gapSize;
	Pipe pipes[2] = {Pipe(w, gapSize + rand() % maxPipeGap, gapSize), Pipe(w + gapBetweenPipes, gapSize + rand() % maxPipeGap, gapSize)};

	int score = 0;
	const int sampleSize = 500;


	std::vector<Bird> birds;
	birds.reserve(sampleSize);

	for (int i = 0; i < sampleSize; i++) {
		birds.push_back(Bird(birdX, h / 2));
	}

	while (true) {
		Uint64 start = SDL_GetPerformanceCounter();
		SDL_SetRenderDrawColor(renderer, 0, 200, 255, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		if (pipes[0].getX() < -pipes[0].getWidth()) {
			pipes[0] = pipes[1];
			pipes[1] = Pipe(pipes[0].getX() + gapBetweenPipes, gapSize + rand() % maxPipeGap, gapSize);
		}

		if (pipes[0].getX() + pipes[0].getWidth() / 2 < birdX && !pipes[0].getPassed()) {
			score += 1;
			pipes[0].setPassed();
			for (int i = 0; i < birds.size(); i++) {
				if (birds[i].getAlive()) {
					birds[i].increaseScore();
				}
			}
		}

		pipes[0].draw(renderer);
		pipes[1].draw(renderer);
		pipes[0].logic();
		pipes[1].logic();
		

		bool allDead = true;
		int drawnCounter = 0;
		for (int i = 0; i < birds.size(); i++) {
			if (birds[i].getAlive()) {
			
				birds[i].draw(renderer);
				
				drawnCounter++; 
				birds[i].logic(pipes[0]);
				allDead = false;
			}
		}

		char scoreChar[1000];
		sprintf_s(scoreChar, "%d", score);
		stringRGBA(renderer, 10, 10, scoreChar, 0, 0, 0, 255);
		SDL_RenderPresent(renderer);

		Uint64 end = SDL_GetPerformanceCounter();


		float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
		// Cap to 60 FPS
		if (1000 / fps - elapsedMS > 0) {
			SDL_Delay(floor(1000 / fps - elapsedMS));
		}
		



		if (allDead) {
			birds = evolvePopulation(birds);
			score = 0;
			pipes[0] = Pipe(w, gapSize + rand() % maxPipeGap, gapSize);
			pipes[1] = Pipe(w + gapBetweenPipes, gapSize + rand() % maxPipeGap, gapSize);
			std::cout << "RESET" << std::endl;
		}
		//SDL_Delay(1000/fps);
	}
	
	return EXIT_SUCCESS;
}

std::vector<Bird> evolvePopulation(std::vector<Bird> birds) {
	const float scoreBonus = 1000;
	float totalFitness = 0;

	for (int i = 0; i < birds.size(); i++) {
		totalFitness += birds[i].getFitness();
	}

	float totalProb = 0;
	for (int i = 0; i < birds.size(); i++) {
		birds[i].setSelectionProbability((1 + birds[i].getFitness()) / (1 + totalFitness));

		totalProb += birds[i].getSelectionProbability();
	}

	std::vector<Bird> newPopulation;
	int counter = 0;

	while (newPopulation.size() < birds.size()) {
		
		float random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * totalProb;
		
		float runningProb = 0;
		for (int i = 0; i < birds.size(); i++) {
			runningProb += birds[i].getSelectionProbability();
			if (random <= runningProb) {
				Bird newBird = Bird(birdX, h / 2);
				newBird.cloneBrain(birds[i]);
				newBird.mutate();
				newPopulation.push_back(newBird);
				break;
			}
		}
	}
	return newPopulation;
}








