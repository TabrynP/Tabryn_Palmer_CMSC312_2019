#ifndef SHORTEST_H
#define SHORTEST_H

#include "Process.h"

// Overloads the "<" operator of the Process class to sort processes
// by their running time
class ShortestJobProcess : public Process {
public:
	ShortestJobProcess(const std::vector<std::string>& program_file, std::shared_ptr<SharedMemory> mem) : Process(program_file, mem) {
		is_shortest_job = true;
	}
	ShortestJobProcess(const Process& old_process) {
		process_map_vector = old_process.process_map_vector;
		process_PCB = old_process.process_PCB;
		children = old_process.children;
		virtual_memory = old_process.virtual_memory;
		is_shortest_job = true;
	}
	~ShortestJobProcess() {
		process_map_vector.clear();
		children.clear();
	}
	// Overload < operator for shortest job first algorithm.
	bool operator< (const ShortestJobProcess& p) const {
		return process_PCB.total_runtime < p.process_PCB.total_runtime;
	}

};

#endif // SHORTEST_H
