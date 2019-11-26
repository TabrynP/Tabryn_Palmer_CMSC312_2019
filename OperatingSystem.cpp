#include "OperatingSystem.h"

OperatingSystem::OperatingSystem(int processes_in) {
	scheduler = Scheduler(50);
	CPU0 = CPU();
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
		auto temp = std::make_shared<Process>(program_files[i]);
		process_vector.push_back(temp);
	}
}

void OperatingSystem::execute_processes() {
	auto s = std::make_shared<Semaphore>();
	auto s_ref = *s;
	auto mem = std::make_shared<MainMemory>();
	auto mem_ref = *mem;
	std::vector<std::shared_ptr<Process>> process_queue = process_vector;
	do {
		scheduler.schedule_processes(process_queue, s_ref, mem_ref);
		if (process_queue.size() != 0) {
			auto running_processes = dispatcher.dispatch_processes(process_queue);
			switch (running_processes.size()) {
			case 1:
				execute_one_thread(running_processes);
			case 2:
				execute_two_threads(running_processes);
			case 3:
				execute_three_threads(running_processes);
			case 4:
				execute_four_threads(running_processes);
			}
		}
		
	} while (scheduler.processes_in_queue());
	std::cout << "All processes executed. Aborting.";
}

void OperatingSystem::execute_one_thread(std::vector<std::shared_ptr<Process>> running) {
	std::thread thread_1(&CPU::execute_program, CPU0, running.begin(), scheduler);
	thread_1.join();
}
void OperatingSystem::execute_two_threads(std::vector<std::shared_ptr<Process>> running) {
	std::thread thread_1(&CPU::execute_program, CPU0, running.begin(), scheduler);
	std::thread thread_2(&CPU::execute_program, CPU0, running.begin(), scheduler);
	thread_1.join();
	thread_2.join();
}
void OperatingSystem::execute_three_threads(std::vector<std::shared_ptr<Process>> running) {
	std::thread thread_1(&CPU::execute_program, CPU0, running.begin(), scheduler);
	std::thread thread_2(&CPU::execute_program, CPU0, running.begin(), scheduler);
	std::thread thread_3(&CPU::execute_program, CPU1, running.begin(), scheduler);
	thread_1.join();
	thread_2.join();
	thread_3.join();
}
void OperatingSystem::execute_four_threads(std::vector<std::shared_ptr<Process>> running) {
	std::thread thread_1(&CPU::execute_program, CPU0, running.begin(), scheduler);
	std::thread thread_2(&CPU::execute_program, CPU0, running.begin(), scheduler);
	std::thread thread_3(&CPU::execute_program, CPU1, running.begin(), scheduler);
	std::thread thread_4(&CPU::execute_program, CPU1, running.begin(), scheduler);
	thread_1.join();
	thread_2.join();
	thread_3.join();
	thread_4.join();
}