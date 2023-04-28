#include "FirstGame2.h"


Game::Game() {
	wind = nullptr;
	isRunning = true;
	paddle1.y = 150;
	paddle1.x = 5;
	paddle2.x = 389;
	paddle2.y = 150;
	ball.y = 190;
	ball.x = 100;
	tickCount = 0;
	int rand = std::rand()%10;
	ballv.x = 170.0f;
	ballv.y = -195.0f;
	score = 0;
}

bool Game::initialise() {
	int strt = SDL_Init(SDL_INIT_VIDEO);
	wind = SDL_CreateWindow("Game program", 400, 100, 400, 400, 0);
	renderer = SDL_CreateRenderer(wind, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (strt != 0 || !wind || !renderer) {
		SDL_Log("Unable to initialize %s. System exited with code 1", SDL_GetError());
		return false;
	}
	else {

		SDL_Log("Code ended with %d", strt);


		return true;
	}
}

void Game::shutDown() {
	SDL_DestroyWindow(wind);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

}

void Game::runLoop() {

	while(isRunning) {
		handleInput();
		updateSys();
		renderOutput();


	}
}

void Game::handleInput() {
	SDL_Event e; paddley1 = 0, paddley2 = 0;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE]) {
		isRunning = false;
	}
	else if (state[SDL_SCANCODE_W]) {
		paddley1 -= 1;

	}
	else if (state[SDL_SCANCODE_S]) {
		paddley1 += 1;

	}
	else if (state[SDL_SCANCODE_O]) {
		paddley2 -= 1;
	
	}
	else if (state[SDL_SCANCODE_K]) {
		paddley2 += 1;

	}


}
void Game::renderOutput() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect wall = { 0,3,1023,15 };
	SDL_RenderFillRect(renderer, &wall);

	wall = { 0,350,1023,15 };
	SDL_RenderFillRect(renderer, &wall);
	SDL_Rect  Paddle1 = { paddle1.x,paddle1.y,6,40 };
	SDL_RenderFillRect(renderer, &Paddle1);
	SDL_Rect  Paddle2 = { paddle2.x,paddle2.y,6,40 };
	SDL_RenderFillRect(renderer, &Paddle2);
	SDL_Rect Ball = { ball.x,ball.y,ballw,ballh };
	SDL_RenderFillRect(renderer, &Ball);

	SDL_RenderPresent(renderer);
}

void Game::updateSys() {
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), tickCount + 16));

	float deltatime = (SDL_GetTicks() - tickCount) / 1000.0f;
	tickCount = SDL_GetTicks();
	if (deltatime > 0.05f) {
		deltatime = 0.05f;
	}
	if (paddley1 != 0) {
		paddle1.y += paddley1 * 300.0f * deltatime;

		if (paddle1.y < (10 / 2.0f + 15))
		{
			paddle1.y = 10 / 2.0f + 15;
		}
		else if (paddle1.y > (413.0f - 70 / 2.0f - 70))
		{
			paddle1.y = 413.0f - 70 / 2.0f - 70;
		}
	}
	else if (paddley2 != 0) {
		paddle2.y += paddley2 * 300.0f * deltatime;

		if (paddle2.y < (10 / 2.0f + 15))
		{
			paddle2.y = 10 / 2.0f + 15;
		}
		else if (paddle2.y > (413.0f - 70 / 2.0f - 70))
		{
			paddle2.y = 413.0f - 70 / 2.0f - 70;
		}
	}



	if (ball.y <= 15 && ballv.y < 0.0f) {
		ballv.y *= -1;
	}
	else if ((ball.x <= paddle1.x + 6) && (ball.y + ballh >= paddle1.y) && (ball.y < paddle1.y + 40) && ballv.x < 0.0f) {
		ballv.x *= -1;
		score += 1;
	}
	else if ((ball.y + ballh >= 350) && ballv.y > 0.0f) {
		ballv.y *= -1;
	}


	else if ((ball.x + ballw >= paddle2.x) && (ball.y + ballh >= paddle2.y) && (ball.y < paddle2.y + 40) && ballv.x > 0.0f) {
		ballv.x *= -1;
		score += 1;
	}

	else if ((ball.x + ballw <= 0) || (ball.x >= 480)) {
		ballv.x = 0.0, ballv.y = 0.0;
		std::cout << "Failed\nScore: " << score;
		isRunning = false;

	}
	ball.x += ballv.x * deltatime;
	ball.y += ballv.y * deltatime;



}
