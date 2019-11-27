#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <iostream>
#include <iterator>
#include "Process.h"
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
	Scheduler() { 
		time_quantum = 100; in_queue = true; 
	}
	Scheduler(int quantum) { 
		time_quantum = quantum;  in_queue = true; 
	}
	void schedule_processes(std::vector<std::shared_ptr<Process>>& process_vector, Semaphore& s, MainMemory& m, int& count);
	bool processes_in_queue() { 
		return in_queue; 
	}
	int get_time_quantum() const { 
		return time_quantum; 
	}
private:
	int time_quantum;
	bool in_queue;
};

void wait(Semaphore& s, std::shared_ptr<Process> p);

void signal(Semaphore& s);

#endif //SCHEDULER_H