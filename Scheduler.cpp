/*
	Note that my scheduling algorithm was derived form the one
	available at the following location:
	https://www.geeksforgeeks.org/program-round-robin-scheduling-set-1/

	It's been heavily modified to be much more betterererer.
*/

#include "Scheduler.h"

std::vector<Process> Scheduler::schedule_processes(std::vector<Process> *processes) {
	in_queue = false;
	std::vector<int> remaining_bt;
	for (int i = 0; i < processes->size(); i++) {
		remaining_bt[i] = processes->at(i).get_total_runtime();
	}
	std::vector<Process> process_queue;
	for (int i = 0; i < processes->size(); i++) {
		remaining_bt.push_back(processes->at(i).get_total_runtime() - time_quantum);
		if (remaining_bt[i] > 0) {
			process_queue.push_back(processes->at(i));
			process_queue[i].set_total_runtime(remaining_bt[i]);
			process_queue[i].update_state(READY);
		}
		else {
			processes->at(i).update_state(EXIT);
		}
	}
	for (int i = 0; i < remaining_bt.size(); i++) {
		if (remaining_bt[i] > 0) {
			in_queue = true;
		}
	}
}
