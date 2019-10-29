// Tabryn Palmer CMSC 312 Project
#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
#include <chrono>
#include <memory>
#include <map>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

#include "PCB.h"

struct ProcessMap {
	ProcessMap(std::string type_in, int runtime_in) {
		type = type_in;
		runtime = runtime_in;
	}
	std::string type;
	int runtime;
};

class Process {
public:
	Process(std::vector<std::string> program_file);
	void update_state(State new_state);
	int get_total_runtime() const { return process_PCB.total_runtime; }
	void set_total_runtime(int total_runtime) { process_PCB.total_runtime = total_runtime; }
	PCB get_PCB() const { return process_PCB; }

private:

	State current_state;
	std::vector<ProcessMap> process_map_vector;
	int memory;
	PCB process_PCB;
};

static int parse_number(std::string);


#endif //PROCESS_H


