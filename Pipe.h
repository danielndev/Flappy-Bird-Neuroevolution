#include<SDL.h>
#include "SDL2_gfxPrimitives.h"


#ifndef Pipe_H
#define Pipe_H

class Pipe {
	private:
		int speed = 4;
		int width = 50;
		bool passed = false;
		float gapSize = 200;
		float gapBottom;
		float x;
	public:
		Pipe(float x, float gapB, float gapSize);
		void draw(SDL_Renderer* renderer);
		void logic();
		float getX();
		float getWidth();
		float getGapSize();
		float getGapBottom();
		bool getPassed();
		void setPassed();
};

#endif
