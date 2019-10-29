#ifndef PCB_H
#define PCB_H

#include <vector>
#include <string>

enum State { NEW, READY, RUN, WAIT, EXIT };

struct PCB {
	State process_state;
	int total_runtime;
	int current_instruction;
	std::string name;
};

#endif // PCB_H


