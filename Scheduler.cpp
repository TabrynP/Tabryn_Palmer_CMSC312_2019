/*
	Note that my scheduling algorithm was derived form the one
	available at the following location:
	https://www.geeksforgeeks.org/program-round-robin-scheduling-set-1/

	It's been heavily modified to be much more betterererer.
*/

#include "Scheduler.h"

static void set_current_state(Process& process, int);
static void print_PCB(Process&);
static void move_to_back(std::vector<std::shared_ptr<Process>>& process_vector, std::vector<std::shared_ptr<Process>>::iterator& i);
static void move_to_front(std::vector<std::shared_ptr<Process>>& process_vector, std::vector<std::shared_ptr<Process>>::iterator& i);
static bool test_memory(std::shared_ptr<Process>, MainMemory&);
static void remove_from_memory(std::shared_ptr<Process>, MainMemory&);

void Scheduler::schedule_processes(std::vector<std::shared_ptr<Process>>& processes, Semaphore& s, MainMemory& m, int& count) {
	in_queue = false;
	std::vector<int> remaining_bt;
	std::vector<std::shared_ptr<Process>>& queue = s.process_queue;
	std::vector<PCB> pcb_vector;
	for (int i = 0; i < processes.size(); i++) {
		pcb_vector.push_back(processes[i]->get_PCB());
	}

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
	int test = 0;
	for (auto i = processes.begin(); i != processes.end(); ++i) {
		auto& process = *(*i);
		if (process.get_PCB().process_state == RUN) {
			set_current_state(process, time_quantum);
			process.update_state(READY);
			move_to_back(processes, i);
		}
		else if (process.get_PCB().process_state == WAIT) {
			if (process.get_current_instruction().type == "I/O" && !(process.is_sleeping())) {
				set_current_state(process, time_quantum);
			}
			else {
				if (!(process.is_sleeping())) {
					process.update_state(READY);
				}
			}
			if (i == processes.end()) {
				auto process_temp = process;
				move_to_back(processes, i);
			}
		}
		else if (process.get_PCB().process_state == EXIT) {
			if (process.is_in_critical()) {
				signal(s);
			}
			if (process.is_parent && process.get_children().size() > 0) {
				auto children = process.get_children();
				for (auto it = children.begin(); it != children.end(); ++it) {
					process.abort(*(*it));
				}
			}
			remove_from_memory(*i, m);
			move_to_back(processes, i);
			count++;
		}
		if (process.get_PCB().process_state != EXIT) {
			if (process.get_current_instruction().type == "I/O") {
				process.update_state(WAIT);
				if (process.get_current_instruction().end_critical && process.is_in_critical()) {
					process.set_critical(false);
					signal(s);
				}
				set_current_state(process, time_quantum);
				move_to_back(processes, i);
			}
			else if (process.get_current_instruction().type == "CALCULATE" && !(process.is_sleeping())) {
				process.update_state(READY);
			}
			else if (process.get_current_instruction().type == "YIELD") {
				move_to_back(processes, i);
			}
			else if (process.get_current_instruction().type == "OUT" && !(process.is_sleeping())) {
				print_PCB(process);
				process.update_state(READY);
			}
			if (process.get_current_instruction().is_critical && !(process.is_in_critical()) && !(process.is_sleeping())) {
				wait(s, *i);
			}
			if (process.get_current_instruction().end_critical && process.is_in_critical()) {
				process.set_critical(false);
				signal(s);
			}
			if (process.is_sleeping()) {
				process.update_state(WAIT);
			}
			if (process.get_random_IO() > 0) {
				process.update_state(WAIT);
				int random_IO = process.get_random_IO() - time_quantum;
				if (random_IO > 0) {
					process.set_random_IO(random_IO);
				}
				else {
					process.set_random_IO(0);
				}
			}
			if ((process.get_state() == READY || process.get_state() == NEW) && !(process.is_in_memory())) {
				if (test_memory(*i, m)) {
					process.update_state(READY);
				}
				else {
					process.update_state(WAIT);
					move_to_back(processes, i);
				}
			}
			if (process.get_state() == WAIT) {
				remove_from_memory(*i, m);
				move_to_back(processes, i);
			}
			else if (process.get_state() == EXIT) {
				remove_from_memory(*i, m);
			}
			test++;
		}	
	}

	// If the process at the top of the queue is not in the READY state, put it back at the beginning of the queue.
	if (processes.size() > 0) {
		if (processes.back()->get_state() != READY) {
			for (auto i = processes.begin(); i != processes.end(); ++i) {
				auto temp = *(*i);
				if (temp.get_state() != READY) {
					move_to_back(processes, i);
				}
			}
		}
	}

	// Move all processes in EXIT state to the back
	int offset = 0;
	for (auto it = processes.begin(); it != processes.end(); ++it) {
		auto temp = (*(*it));
		if (temp.get_state() == EXIT) {
			if (temp.is_in_critical()) {
				signal(s);
			}
			if (temp.is_sleeping()) {

			}
			offset++;
			move_to_back(processes, it);
		}
	}

	// Delete processes from the back of the queue until they no longer equal EXIT
	if (offset > 0 && offset < processes.size()) {
		processes.erase(processes.begin() + offset, processes.end());
	}
	else if (offset >= processes.size()) {
		processes.clear();
	}

	for (int i = 0; i < remaining_bt.size(); i++) {
		if (remaining_bt[i] > 0) {
			in_queue = true;
			break;
		}
	}
}

static void move_to_back(std::vector<std::shared_ptr<Process>>& processes, std::vector<std::shared_ptr<Process>>::iterator& i) {
	std::rotate(processes.begin(), i, i + 1);
}

static void set_current_state(Process& process, int time_quantum) {
	int temp = process.get_PCB().current_instruction;
	while (time_quantum > 0) {
		if (process.process_map(temp).runtime < time_quantum && time_quantum > 0) {
			int total_runtime = process.get_total_runtime() - process.process_map(temp).runtime;
			time_quantum = time_quantum - process.process_map(temp).runtime;
			process.set_current_instruction(++temp);
			process.set_total_runtime(total_runtime);
		}
		else {
			int total_runtime = process.get_total_runtime() - time_quantum;
			ProcessMap temp_map = process.process_map(temp);
			temp_map.runtime = temp_map.runtime - time_quantum;
			process.set_process_map(temp_map, temp);
			process.set_total_runtime(total_runtime);
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

static bool test_memory(std::shared_ptr<Process> process, MainMemory& m) {
	int current_mem = m.used_memory();
	if (m.add_page(process)) {
		return true;
	}
	else {
		return false;
	}
}

static void remove_from_memory(std::shared_ptr<Process> process, MainMemory& m) {
	if (m.has_page(process)) {
		m.delete_page(process);
	}
}


void wait(Semaphore& s, std::shared_ptr<Process> p) {
	s.value--;
	bool in_queue = false;
	if (s.value < 0) {
		for (auto it = s.process_queue.begin(); it != s.process_queue.end(); ++it) {
			auto temp = *it;
			if (temp == p) {
				in_queue = true;
			}
		}
		if (!in_queue) {
			s.process_queue.push_back(p);
			p->sleep();
			p->set_critical(false);
		}
	}
	else {
		p->wakeup();
		p->set_critical(true);
	}
}

void signal(Semaphore& s) {
	s.value++;
	if (s.value <= 0) {
		s.process_queue.back()->set_critical(true);
		s.process_queue.back()->wakeup();
		s.process_queue.pop_back();
	}
}
