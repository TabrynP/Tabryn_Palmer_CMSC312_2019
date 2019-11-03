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
	ProcessMap(std::string type_in, int runtime_in, bool is_critical_in, bool end_critical_in) {
		type = type_in;
		runtime = runtime_in;
		is_critical = is_critical_in;
		end_critical = end_critical_in;
	}
	std::string type;
	int runtime;
	bool is_critical;
	bool end_critical;
};

class Process {
public:
	Process(const std::vector<std::string>& program_file);
	Process(const Process& old_process) {
		current_state = old_process.current_state;
		process_map_vector = old_process.process_map_vector;
		process_PCB = old_process.process_PCB;
	}
	~Process() {
		process_map_vector.clear();
	}
	void update_state(State new_state);
	int get_total_runtime() const {
		return process_PCB.total_runtime;
	}
	void set_total_runtime(int total_runtime) { 
		process_PCB.total_runtime = total_runtime; 
	}
	PCB get_PCB() const { 
		return process_PCB; 
	}
	State get_state() {
		return process_PCB.process_state;
	}
	ProcessMap get_current_instruction() {
		return process_map_vector[process_PCB.current_instruction];
	}
	void set_current_instruction(int in) {
		process_PCB.current_instruction = in;
	}
	ProcessMap process_map(int in) {
		return process_map_vector[in];
	}
	void set_process_map(ProcessMap in_map, int in) {
		process_map_vector[in] = in_map;
	}
	void sleep() {
		process_PCB.is_sleeping = true;
	}
	void wakeup() {
		process_PCB.is_sleeping = false;
	}
	bool is_sleeping() {
		return process_PCB.is_sleeping;
	}
	bool is_in_critical() {
		return process_PCB.in_critical;
	}
	void set_critical(bool in) {
		process_PCB.in_critical = in;
	}
	bool is_in_memory() {
		return process_PCB.in_memory;
	}
	void set_in_memory(bool in) {
		process_PCB.in_memory = in;
	}

private:
	State current_state;
	std::vector<ProcessMap> process_map_vector;
	PCB process_PCB;
};

static int parse_number(std::string);


#endif //PROCESS_H


