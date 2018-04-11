#include "parameters.h"
#include "clientProgram.h"

int main(int argc, char *argv[]) {

	std::string server_hostname;

	if (argc == 2) {
		server_hostname = argv[1];
	}
	else if (argc == 1) {
		server_hostname = SERVER_ADDRESS;
	}
	else {
		std::cout << "Expected 0 or 1 argument : hostname" << '\n';
		return 1;
	}

	initSettings();
	Program program(server_hostname);
	program.init();
	program.run();

	return 0;
}
