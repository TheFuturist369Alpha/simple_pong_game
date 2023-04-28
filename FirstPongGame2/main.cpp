#include "FirstGame2.h"

int main(int num, char* arr[]) {
	Game newGame;
	bool start = 
		newGame.initialise();
	if (start) {
		newGame.runLoop();
	}
	newGame.shutDown();

	return 0;
}