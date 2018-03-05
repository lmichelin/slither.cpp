#include "parameters.h"
#include "program.h"

int main() {
	std::srand(time(NULL)); // use current time as seed for random generator
	Program program(PORT);
	program.init();
	program.run();

	return 0;
}
