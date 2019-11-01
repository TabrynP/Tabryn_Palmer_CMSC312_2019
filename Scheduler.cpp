/*
	Note that my scheduling algorithm was derived form the one
	available at the following location:
	https://www.geeksforgeeks.org/program-round-robin-scheduling-set-1/

	It's been heavily modified to be much more betterererer.
*/

#include "Scheduler.h"

static void set_current_state(std::shared_ptr<Process>, int);
static void print_PCB(std::shared_ptr<Process>);
static void move_to_back(std::vector<std::shared_ptr<Process>>& process_vector, int i);

void Scheduler::schedule_processes(std::vector<std::shared_ptr<Process>>& processes, std::shared_ptr<Semaphore> s) {
	in_queue = false;
	std::vector<int> remaining_bt;
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
			processes[i]->update_state(READY);
			move_to_back(processes, i);
		}
		else if (processes[i]->get_PCB().process_state == WAIT) {
			if (processes[i]->get_current_instruction().type == "I/O" && !(processes[i]->is_sleeping())) {
				set_current_state(processes[i], time_quantum);
			}
			else {
				if (!(processes[i]->is_sleeping())) {
					processes[i]->update_state(READY);
				}
			}
			if (i == (processes.size() - 1)) {
				auto process_temp = processes[i];
				move_to_back(processes, i);
			}
		}
		else if (processes[i]->get_PCB().process_state == EXIT) {
			if (processes[i]->is_in_critical()) {
				signal(s);
			}
			processes.erase(processes.begin() + i);
			break;
		}
		if (processes[i]->get_current_instruction().type == "I/O") {
			processes[i]->update_state(WAIT);
			if (processes[i]->get_current_instruction().end_critical && processes[i]->is_in_critical()) {
				processes[i]->set_critical(false);
				signal(s);
			}
			set_current_state(processes[i], time_quantum);
			move_to_back(processes, i);
		}
		else if (processes[i]->get_current_instruction().type == "CALCULATE" && !(processes[i]->is_sleeping())) {
			processes[i]->update_state(READY);
		}
		else if (processes[i]->get_current_instruction().type == "YIELD") {
			auto temp = processes[i];
			move_to_back(processes, i);
		}
		else if (processes[i]->get_current_instruction().type == "OUT" && !(processes[i]->is_sleeping())) {
			print_PCB(processes[i]);
			processes[i]->update_state(READY);
		}
		if (processes[i]->get_current_instruction().is_critical && !(processes[i]->is_in_critical()) && !(processes[i]->is_sleeping())) {
			wait(s, processes[i]);
		}
		if (processes[i]->get_current_instruction().end_critical && processes[i]->is_in_critical()) {
			processes[i]->set_critical(false);
			signal(s);
		}
		if (processes[i]->is_sleeping()) {
			processes[i]->update_state(WAIT);
		}
	}
	// If the process at the top of the queue is not in the READY state, put it back at the beginning of the queue.
	if (processes.size() > 0) {
		if (processes.back()->get_state() != READY) {
			auto temp = processes.back();
			processes.pop_back();
			processes.insert(processes.begin(), temp);
		}
	}
	for (int i = 0; i < remaining_bt.size(); i++) {
		if (remaining_bt[i] > 0) {
			in_queue = true;
			break;
		}
	}
}

static void move_to_back(std::vector<std::shared_ptr<Process>>& processes, int i) {
	auto process_temp = processes[i];
	processes.erase(processes.begin() + i);
	processes.insert(processes.begin(), process_temp);
}

static void set_current_state(std::shared_ptr<Process> process, int time_quantum) {
	int temp = process->get_PCB().current_instruction;
	while (time_quantum > 0) {
		if (process->process_map(temp).runtime < time_quantum && time_quantum > 0) {
			int total_runtime = process->get_total_runtime() - process->process_map(temp).runtime;
			time_quantum = time_quantum - process->process_map(temp).runtime;
			process->set_current_instruction(++temp);
			process->set_total_runtime(total_runtime);
		}
		else {
			int total_runtime = process->get_total_runtime() - time_quantum;
			ProcessMap temp_map = process->process_map(temp);
			temp_map.runtime = temp_map.runtime - time_quantum;
			process->set_process_map(temp_map, temp);
			process->set_total_runtime(total_runtime);
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

void wait(std::shared_ptr<Semaphore> s, std::shared_ptr<Process> p) {
	s->value--;
	if (s->value < 0) {
		s->process_queue.push_back(p);
		p->sleep();
	}
	else {
		p->set_critical(true);
	}
}

void signal(std::shared_ptr<Semaphore> s) {
	s->value++;
	if (s->value <= 0) {
		s->process_queue.back()->set_critical(true);
		s->process_queue.back()->wakeup();
		s->process_queue.pop_back();
	}
}
