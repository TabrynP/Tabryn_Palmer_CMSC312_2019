#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include "Process.h"
#include "ShortestJobProcess.h"
#include "MainMemory.h"

struct Semaphore {
	std::vector<std::shared_ptr<Process>> process_queue;
	int value;
	Semaphore() {
		value = 1;
		process_queue.clear();
	}
};

class Scheduler {
public:
	Scheduler(int quantum, int job_type) {
		time_quantum = quantum; scheduler_type = job_type; in_queue = true;
	}
	Scheduler() : Scheduler(100, 0) {
		in_queue = true;
	}
	Scheduler(int quantum) : Scheduler(quantum, 0) {
		time_quantum = quantum;  in_queue = true;
	}
	void schedule_processes(std::vector<std::shared_ptr<Process>>& process_vector, Semaphore& s);
	bool processes_in_queue() { 
		return in_queue; 
	}
	int get_time_quantum() const { 
		return time_quantum; 
	}
private:
	int time_quantum;
	bool in_queue;
	int scheduler_type;
	void shortest_job_first(std::vector<std::shared_ptr<Process>>& process_vector, Semaphore& s);
	void round_robin(std::vector<std::shared_ptr<Process>>& process_vector, Semaphore& s);
	std::vector<std::shared_ptr<Process>> check_IO(std::vector<std::shared_ptr<Process>>& process_vector, Semaphore& s);
};

void wait(Semaphore& s, std::shared_ptr<Process> p);

void signal(Semaphore& s);

#endif //SCHEDULER_H