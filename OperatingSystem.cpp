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
			dispatcher.dispatch_processes(process_queue);
			if (process_queue.back()->get_state() == RUN) {
				CPU0.execute_program(process_queue.back(), scheduler);
			}
		}
		
	} while (scheduler.processes_in_queue());
	std::cout << "All processes executed. Aborting.";
}
