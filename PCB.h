#ifndef PCB_H
#define PCB_H

#include <vector>
#include <string>

enum State { NEW, READY, RUN, WAIT, EXIT };

struct PCB {
	PCB() {
		process_state = NEW;
		total_runtime = 0;
		current_instruction = 0;
		name = "";
		is_sleeping = false;
		in_critical = false;
		memory = 0;
		in_memory = false;
		random_IO = 0;
		program_file = "";
	}
	PCB(const PCB& old_PCB) {
		process_state = old_PCB.process_state;
		total_runtime = old_PCB.total_runtime;
		current_instruction = old_PCB.current_instruction;
		name = old_PCB.name;
		is_sleeping = old_PCB.is_sleeping;
		in_critical = old_PCB.in_critical;
		memory = old_PCB.memory;
		in_memory = old_PCB.in_memory;
		random_IO = old_PCB.random_IO;
		program_file = old_PCB.program_file;
	}
	State process_state;
	int total_runtime;
	int current_instruction;
	std::string name;
	bool is_sleeping;
	bool in_critical;
	int memory;
	bool in_memory;
	int random_IO;
	std::string program_file;
};

static bool operator==(const PCB& PCB1, const PCB& PCB2) {
	return
		PCB1.process_state == PCB2.process_state
		&& PCB1.total_runtime == PCB2.total_runtime
		&& PCB1.current_instruction == PCB2.current_instruction
		&& PCB1.name == PCB2.name
		&& PCB1.is_sleeping == PCB2.is_sleeping
		&& PCB1.in_critical == PCB2.in_critical
		&& PCB1.memory == PCB2.memory
		&& PCB1.in_memory == PCB2.in_memory
		&& PCB1.random_IO == PCB2.random_IO;
}

#endif // PCB_H


