#include "parameters.h"
#include "serverProgram.h"

int main() {
	std::srand(time(NULL)); // use current time as seed for random generator
	Program program(SERVER_PORT);
	program.init();
	program.run();

	return 0;
}
