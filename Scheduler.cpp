/*
	Note that my scheduling algorithm was derived form the one
	available at the following location:
	https://www.geeksforgeeks.org/program-round-robin-scheduling-set-1/

	It's been heavily modified to be much more betterererer.
*/

#include "Scheduler.h"

static void set_current_state(Process&, int);
static void print_PCB(Process&);

std::vector<Process> Scheduler::schedule_processes(std::vector<Process> *processes) {
	in_queue = false;
	std::vector<int> remaining_bt;
	std::vector<Process> process_queue;
	for (int i = 0; i < processes->size(); i++) {
		remaining_bt.push_back(processes->at(i).get_total_runtime() - time_quantum);
		if (remaining_bt[i] > 0 && processes->at(i).get_PCB().process_state != EXIT) {
			process_queue.push_back(processes->at(i));
		}
		else {
			std::cout << "Process " << processes->at(i).get_PCB().name << " completed. " << std::endl;
			processes->at(i).update_state(EXIT);
		}
	}
	for (int i = 0; i < process_queue.size(); i++) {
		if (process_queue[i].get_PCB().process_state == RUN) {
			set_current_state(process_queue[i], time_quantum);
		}
		else if (process_queue[i].get_PCB().process_state == WAIT) {
			if (process_queue[i].get_current_instruction().type == "I/O") {
				process_queue[i].set_total_runtime(remaining_bt[i]);
			}
			else {
				process_queue[i].update_state(READY);
			}
		}
		if (process_queue[i].get_current_instruction().type == "I/O") {
			process_queue[i].update_state(WAIT);
		}
		else if (process_queue[i].get_current_instruction().type == "CALCULATE") {
			process_queue[i].update_state(READY);
		}
		else if (process_queue[i].get_current_instruction().type == "YIELD") {
			Process temp = process_queue[i];
			process_queue.erase(process_queue.begin() + (i - 1));
			process_queue.insert(process_queue.begin(), temp);
			process_queue.front().update_state(READY);
		}
		else if (process_queue[i].get_current_instruction().type == "OUT") {
			print_PCB(process_queue[i]);
			process_queue[i].update_state(READY);
		}
	}
	for (int i = 0; i < remaining_bt.size(); i++) {
		if (remaining_bt[i] > 0) {
			in_queue = true;
			break;
		}
	}
	return process_queue;
}

static void set_current_state(Process& process, int time_quantum) {
	int temp = process.get_PCB().current_instruction;
	while (time_quantum > 0) {
		if (process.process_map(temp).runtime < time_quantum) {
			time_quantum = time_quantum - process.process_map(temp).runtime;
			process.set_current_instruction(temp++);
		}
		else {
			ProcessMap temp_map = process.process_map(temp);
			temp_map.runtime = temp_map.runtime - time_quantum;
			process.set_process_map(temp_map, temp);
			time_quantum = 0;
		}
	}
	
}

static void print_PCB(Process& process) {
	for (int i = 0; i < process.get_current_instruction().runtime; i++) {}
	PCB pcb = process.get_PCB();
	std::cout << "Process Name: " << pcb.name << std::endl;
	std::cout << "Process remaining runtime: " << pcb.total_runtime << std::endl;
	std::cout << "Process current instruction: " << pcb.current_instruction << std::endl;
}
