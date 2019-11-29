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
#include "SharedMemory.h"
#include "VirtualMemory.h"

struct ProcessMap {
	ProcessMap(std::string type_in, int runtime_in, bool is_critical_in, bool end_critical_in) {
		type = type_in;
		runtime = runtime_in;
		is_critical = is_critical_in;
		end_critical = end_critical_in;
	}
	friend static bool operator==(const ProcessMap& p1, const ProcessMap& p2);
	std::string type;
	int runtime;
	bool is_critical;
	bool end_critical;
};

static bool operator==(const ProcessMap& p1, const ProcessMap& p2) {
	return
		p1.type == p2.type
		&& p1.runtime == p2.runtime
		&& p1.is_critical == p2.is_critical
		&& p1.end_critical == p2.end_critical;
}

class Process {
public:
	friend class ShortestJobProcess;
	Process(const std::string& program_file, std::shared_ptr<SharedMemory> mem);
	Process(const std::string& program_file) : Process(program_file, std::make_shared<SharedMemory>()) {}
	Process(const Process& old_process);
	Process() : Process("Process_1", std::make_shared<SharedMemory>()) {}
	~Process() {
		process_map_vector.clear();
		children.clear();
	}
	friend static bool operator==(const Process& p1, const Process& p2);
	bool operator< (const Process& p) const {
		return priority < p.priority;
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
	void set_random_IO(int in) {
		process_PCB.random_IO = in;
	}
	int get_random_IO() {
		return process_PCB.random_IO;
	}

	std::vector<std::shared_ptr<Process>>& get_children() {
		return children;
	}
	void set_child(std::shared_ptr<Process> child_in) {
		children.push_back(child_in);
	}
	std::shared_ptr<Process> fork();

	int get_priority() {
		return priority;
	}
	void set_priority(int in) {
		priority = in;
	}

	void abort(Process& child);
	bool is_child;
	bool is_parent;
	bool just_ran;
	bool is_shortest_job;

private:
	std::vector<ProcessMap> process_map_vector;
	PCB process_PCB;
	std::vector<std::shared_ptr<Process>> children;
	std::shared_ptr<SharedMemory> shared_memory;
	int priority;
	VirtualMemory virtual_memory;

	void init_process(const std::vector<std::string>& program_file);
	std::vector<std::string> init_program_file(const std::string& file_in);
};

static int parse_number(std::string);

static bool operator==(const Process& p1, const Process& p2) {
	if (
		p1.process_map_vector == p2.process_map_vector &&
		p1.children == p2.children &&
		p1.shared_memory == p2.shared_memory
		) {
		return true;
	}
	else {
		return false;
	}
}

#endif //PROCESS_H
