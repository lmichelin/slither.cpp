#include "parameters.h"
#include "serverProgram.h"

Program Program::program(SERVER_PORT);

int main() {
	std::srand(time(NULL)); // use current time as seed for random generator
	Program::instance().init();
	Program::instance().run();
	return 0;
}