#include "GameEngine.h"



int main() {
	uint8_t i = 15;
	uint8_t j = 15;
	GameEngine ge(i, 0.2f);
	std::cout << ge;

	GameEngine gi(20, 20, 5, 5, ge.GetBoard());
	std::cout << gi;
	std::cin.get();
	gi.Start();
}