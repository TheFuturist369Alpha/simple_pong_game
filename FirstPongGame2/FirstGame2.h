
#ifndef FIRSTGAME
#define FIRSTGAME

#include<SDL.h>
#include <iostream>

#include <cstdlib>

struct vect {
	float x;
	float y;
};

class Game {
public:
	Game();
	bool initialise();

	void runLoop();
	void shutDown();

private:
	void handleInput();
	void updateSys();
	void renderOutput();
	vect paddle1, paddle2;
	vect ball;
	vect ballv;
	Uint32 tickCount;
	int paddley1, paddley2;
	int ballh = 10, ballw = 10;
	int score;


	bool isRunning;
	SDL_Window* wind;
	SDL_Renderer* renderer;


};

#endif