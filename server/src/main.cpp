#include "parameters.h"
#include "program.h"

int main() {
	Program program(PORT);
	program.init();
	program.run();

	return 0;
}
