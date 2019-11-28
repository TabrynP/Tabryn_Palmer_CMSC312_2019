#include "OperatingSystem.h"

OperatingSystem::OperatingSystem(int processes_in) {
	scheduler = Scheduler(50);
	CPU0 = CPU();
	CPU1 = CPU();
	dispatcher = Dispatcher();
	page_table = std::make_shared<PageTable>();
	num_processes = processes_in;
	time_quantum = 50;
}

void OperatingSystem::read_program_file(std::string filename) {
	std::string line;
	std::ifstream program_file;
	program_file.open(filename);
	std::cout << "reading program file. . . \n";
	if (program_file.is_open()) {
		std::vector<std::string> file_lines;
		while (std::getline(program_file, line)) {
			file_lines.push_back(line);
		}
		program_files.push_back(file_lines);
	}
	std::cout << "Read the following files: " << std::endl;
	for (int i = 0; i < program_files.size(); i++) {
		for (int j = 0; j < program_files[i].size(); j++) {
			std::cout << program_files[i][j] << std::endl;
		}
		std::cout << std::endl;
	}
}

void OperatingSystem::create_processes() {
	for (int i = 0; i < program_files.size(); i++) {
		auto temp_mem = std::make_shared<SharedMemory>();
		auto temp = std::make_shared<Process>(program_files[i]);
		process_vector.push_back(temp);
	}
}

void OperatingSystem::execute_processes() {
	auto s = std::make_shared<Semaphore>();
	auto s_ref = *s;
	auto mem = std::make_shared<MainMemory>();
	auto mem_ref = *mem;
	auto page_ref = *page_table;
	create_children();
	std::vector<std::shared_ptr<Process>> process_queue = process_vector;
	do {
		auto ready_queue = update_process_states(process_queue, s_ref, mem_ref, page_ref);
		scheduler.schedule_processes(ready_queue, s_ref);
		if (process_queue.size() != 0) {
			auto running_processes = dispatcher.dispatch_processes(ready_queue);
			switch (running_processes.size()) {
			case 1:
				execute_one_thread(running_processes, process_queue);
				break;
			case 2:
				execute_two_threads(running_processes, process_queue);
				break;
			case 3:
				execute_three_threads(running_processes, process_queue);
				break;
			case 4:
				execute_four_threads(running_processes, process_queue);
				break;
			default:
				break;
			}
		}
		process_vector = process_queue;
		
	} while (scheduler.processes_in_queue());
	std::cout << "All processes executed. Aborting.";
}

void OperatingSystem::execute_one_thread(const std::vector<std::shared_ptr<Process>>& running, std::vector<std::shared_ptr<Process>>& process_queue) {
	std::thread thread_1(&CPU::execute_program, CPU0, std::ref(*(*running.begin())), std::ref(scheduler), std::ref(process_queue));
	thread_1.join();
}
void OperatingSystem::execute_two_threads(const std::vector<std::shared_ptr<Process>>& running, std::vector<std::shared_ptr<Process>>& process_queue) {
	std::thread thread_1(&CPU::execute_program, CPU0, std::ref(*(*running.begin())), std::ref(scheduler), std::ref(process_queue));
	std::thread thread_2(&CPU::execute_program, CPU0, std::ref(*(*(running.begin() + 1))), std::ref(scheduler), std::ref(process_queue));
	thread_1.join();
	thread_2.join();
}
void OperatingSystem::execute_three_threads(const std::vector<std::shared_ptr<Process>>& running, std::vector<std::shared_ptr<Process>>& process_queue) {
	std::thread thread_1(&CPU::execute_program, CPU0, std::ref(*(*running.begin())), std::ref(scheduler), std::ref(process_queue));
	std::thread thread_2(&CPU::execute_program, CPU0, std::ref(*(*(running.begin() + 1))), std::ref(scheduler), std::ref(process_queue));
	std::thread thread_3(&CPU::execute_program, CPU1, std::ref(*(*(running.begin() + 2))), std::ref(scheduler), std::ref(process_queue));
	thread_1.join();
	thread_2.join();
	thread_3.join();
}
void OperatingSystem::execute_four_threads(const std::vector<std::shared_ptr<Process>>& running, std::vector<std::shared_ptr<Process>>& process_queue) {
	std::thread thread_1(&CPU::execute_program, CPU0, std::ref(*(*running.begin())), std::ref(scheduler), std::ref(process_queue));
	std::thread thread_2(&CPU::execute_program, CPU0, std::ref(*(*(running.begin() + 1))), std::ref(scheduler), std::ref(process_queue));
	std::thread thread_3(&CPU::execute_program, CPU1, std::ref(*(*(running.begin() + 2))), std::ref(scheduler), std::ref(process_queue));
	std::thread thread_4(&CPU::execute_program, CPU1, std::ref(*(*(running.begin() + 3))), std::ref(scheduler), std::ref(process_queue));
	thread_1.join();
	thread_2.join();
	thread_3.join();
	thread_4.join();
}

void OperatingSystem::create_children() {
	std::vector<std::shared_ptr<Process>> children;
	srand(time(NULL));
	// Spawn between zero and five children for each process.
	for (int i = 0; i < process_vector.size(); i++) {
		int processes = rand() % 5;
		for (int j = 0; j < processes; j++) {
			children.push_back(process_vector[i]->fork());
		}
	}
	for (int i = 0; i < children.size(); i++) {
		process_vector.push_back(children[i]);
	}
}

void OperatingSystem::prioritize_processes() {
	for (auto it = process_vector.begin(); it != process_vector.end(); ++it) {
		srand(time(NULL));
		int priority = rand() % 1000 + 1; //priority is between 1 and 1000;
		auto temp = *(*it);
		temp.set_priority(priority);
	}
}

std::vector<std::shared_ptr<Process>> OperatingSystem::update_process_states(std::vector<std::shared_ptr<Process>>& processes, Semaphore& s, MainMemory& m, PageTable& t) {
	in_queue = false;
	std::vector<int> remaining_bt;
	std::vector<std::shared_ptr<Process>>& queue = s.process_queue;
	std::vector<PCB> pcb_vector;
	for (int i = 0; i < processes.size(); i++) {
		pcb_vector.push_back(processes[i]->get_PCB());
	}
	for (int i = 0; i < processes.size(); i++) {
		remaining_bt.push_back(processes.at(i)->get_total_runtime() - time_quantum);
	}
	int test = 0;
	for (auto i = processes.begin(); i != processes.end(); ++i) {
		auto& process = *(*i);
		if (process.get_PCB().process_state == RUN) {
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
		}
		if (process.get_PCB().process_state != EXIT) {
			if (process.get_current_instruction().type == "CALCULATE" && !(process.is_sleeping())) {
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
			if ((process.get_state() == READY || process.get_state() == NEW) && !(process.is_in_memory())) {
				if (test_memory(*i, m, t)) {
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
		processes.erase(processes.begin(), processes.begin() + (offset));
	}
	else if (offset >= processes.size()) {
		processes.clear();
	}

	// Move all not READY processes to the back of the queue
	for (auto it = processes.begin(); it != processes.end(); ++it) {
		auto& temp = (*(*it));
		if (temp.get_PCB().process_state != READY) {
			move_to_back(processes, it);
		}
	}

	// Create and return the queue of ready processes for the scheduler.
	std::vector<std::shared_ptr<Process>> ready_queue;
	for (auto it = processes.begin(); it != processes.end(); ++it) {
		auto& temp = (*(*it));
		if (temp.get_PCB().process_state == READY) {
			ready_queue.push_back(*it);
		}
	}
	// Make sure all processes have some burst time remaining.
	for (int i = 0; i < remaining_bt.size(); i++) {
		if (remaining_bt[i] > 0) {
			in_queue = true;
			break;
		}
	}

	return ready_queue;
}

std::vector<std::shared_ptr<Process>> OperatingSystem::get_ready_processes(std::vector<std::shared_ptr<Process>> & processes) {
	std::vector<std::shared_ptr<Process>> ready_queue;
	for (auto it = processes.begin(); it != processes.end(); ++it) {
		auto temp = *(*it);
		if (temp.get_PCB().process_state == READY) {
			ready_queue.push_back(*it);
		}
	}
	return ready_queue;
}

void OperatingSystem::order_by_priority(std::vector<std::shared_ptr<Process>> processes) {
	std::sort(processes.begin(), processes.end());
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

static bool test_memory(std::shared_ptr<Process> process, MainMemory& m, PageTable& t) {
	if (t.send_pages(process, m)) {
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
