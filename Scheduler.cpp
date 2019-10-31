/*
	Note that my scheduling algorithm was derived form the one
	available at the following location:
	https://www.geeksforgeeks.org/program-round-robin-scheduling-set-1/

	It's been heavily modified to be much more betterererer.
*/

#include "Scheduler.h"

static void set_current_state(std::shared_ptr<Process>, int);
static void print_PCB(std::shared_ptr<Process>);

void Scheduler::schedule_processes(std::vector<std::shared_ptr<Process>>& processes, Semaphore& s) {
	in_queue = false;
	std::vector<int> remaining_bt;
	std::vector<std::shared_ptr<Process>> processes;
	for (int i = 0; i < processes.size(); i++) {
		remaining_bt.push_back(processes.at(i)->get_total_runtime() - time_quantum);
		if (remaining_bt[i] > 0 && processes.at(i)->get_PCB().process_state != EXIT) {
			continue;
		}
		else {
			std::cout << "Process " << processes.at(i)->get_PCB().name << " completed. " << std::endl;
			processes.at(i)->update_state(EXIT);
		}
	}
	for (int i = 0; i < processes.size(); i++) {
		if (processes[i]->get_PCB().process_state == RUN) {
			set_current_state(processes[i], time_quantum);
		}
		else if (processes[i]->get_PCB().process_state == WAIT) {
			if (processes[i]->get_current_instruction().type == "I/O") {
				processes[i]->set_total_runtime(remaining_bt[i]);
			}
			else {
				processes[i]->update_state(READY);
			}
		}
		if (processes[i]->get_current_instruction().type == "I/O") {
			processes[i]->update_state(WAIT);
		}
		else if (processes[i]->get_current_instruction().type == "CALCULATE") {
			processes[i]->update_state(READY);
		}
		else if (processes[i]->get_current_instruction().type == "YIELD") {
			std::shared_ptr<Process> temp = processes[i];
			processes.erase(processes.begin() + (i - 1));
			processes.insert(processes.begin(), temp);
			processes.front()->update_state(READY);
		}
		else if (processes[i]->get_current_instruction().type == "OUT") {
			print_PCB(processes[i]);
			processes[i]->update_state(READY);
		}
		if (processes[i]->get_current_instruction().is_critical) {
			wait(s, processes[i]);
		}
		if (processes[i]->get_current_instruction().end_critical) {
			signal(s);
		}
		if (processes[i]->is_sleeping()) {
			processes[i]->update_state(WAIT);
		}
	}
	for (int i = 0; i < remaining_bt.size(); i++) {
		if (remaining_bt[i] > 0) {
			in_queue = true;
			break;
		}
	}
	return processes;
}

static void set_current_state(std::shared_ptr<Process> process, int time_quantum) {
	int temp = process->get_PCB().current_instruction;
	while (time_quantum > 0) {
		if (process->process_map(temp).runtime < time_quantum) {
			time_quantum = time_quantum - process->process_map(temp).runtime;
			process->set_current_instruction(temp++);
		}
		else {
			ProcessMap temp_map = process->process_map(temp);
			temp_map.runtime = temp_map.runtime - time_quantum;
			process->set_process_map(temp_map, temp);
			time_quantum = 0;
		}
	}
	
}

static void print_PCB(std::shared_ptr<Process> process) {
	for (int i = 0; i < process->get_current_instruction().runtime; i++) {}
	PCB pcb = process->get_PCB();
	std::cout << "Process Name: " << pcb.name << std::endl;
	std::cout << "Process remaining runtime: " << pcb.total_runtime << std::endl;
	std::cout << "Process current instruction: " << pcb.current_instruction << std::endl;
}

void wait(Semaphore& s, std::shared_ptr<Process> p) {
	s.value--;
	if (s.value < 0) {
		s.processes.push_back(p);
		p->sleep();
	}
}

void signal(Semaphore& s) {
	s.value++;
	if (s.value <= 0) {
		s.processes.back()->wakeup();
		s.processes.pop_back();
	}
}
