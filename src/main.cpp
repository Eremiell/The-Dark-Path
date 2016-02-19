#include <iostream>
#include <exception>
#include "inc/game.hpp"

int main() {
	try {
		tdp::Game game;
		game.run();
	}
	catch (std::exception &e) {
		std::cerr << std::endl << "EXCEPTION: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
