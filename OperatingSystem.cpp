#include "OperatingSystem.h"

OperatingSystem::OperatingSystem(int processes_in) {
	scheduler = Scheduler(50);
	CPU0 = CPU();
	CPU1 = CPU();
	dispatcher = Dispatcher();
	num_processes = processes_in;
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
	std::shared_ptr<int> count = std::make_shared<int>(0);
	create_children();
	std::vector<std::shared_ptr<Process>> process_queue = process_vector;
	do {
		scheduler.schedule_processes(process_queue, s_ref, mem_ref, *count);
		*count = 0;
		if (process_queue.size() != 0) {
			auto running_processes = dispatcher.dispatch_processes(process_queue);
			switch (running_processes.size()) {
			case 1:
				execute_one_thread(running_processes);
				break;
			case 2:
				execute_two_threads(running_processes);
				break;
			case 3:
				execute_three_threads(running_processes);
				break;
			case 4:
				execute_four_threads(running_processes);
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
