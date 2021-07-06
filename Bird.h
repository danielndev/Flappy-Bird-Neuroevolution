#include<SDL.h>
#include "SDL2_gfxPrimitives.h"
#include "Pipe.h"
#include "NeuralNetwork.h"
#include <time.h>
#ifndef Bird_H
#define Bird_H

class Bird {
	private:
		float x;
		float y;
		float col[3];
		float gravity = 1;
		float size = 15;
		float jumpStrength = 12;
		float vy = 0;
		int score = 0;
		bool alive = true;
		NeuralNetwork brain = NeuralNetwork(3, 3, 1);
		float selectionProbability;
		time_t timer;
		int startTime;
		float fitness;

	public:
		Bird(float x, float y);
		void draw(SDL_Renderer* renderer);
		void logic(Pipe closestPipe);
		void die();
		void jump();
		bool getAlive();
		void increaseScore();
		int getScore();
		void setSelectionProbability(float prob);
		float getSelectionProbability();
		void cloneBrain(Bird b);
		NeuralNetwork getBrain();
		void setBrain(NeuralNetwork b);
		void mutate();
		float getFitness();
};

#endif