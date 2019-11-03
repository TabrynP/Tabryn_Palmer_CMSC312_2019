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
	bool is_sleeping;
	bool in_critical;
	int memory;
	bool in_memory;
	int random_IO;
};

#endif // PCB_H


