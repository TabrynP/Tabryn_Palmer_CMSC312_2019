#include "OperatingSystem.h"

OperatingSystem::OperatingSystem(int processes_in) {
	scheduler = Scheduler(500);
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
		while (!program_file.eof()) {
			program_file >> line;
			file_lines.push_back(line);
		}
		program_files.push_back(file_lines);
	}
}

void OperatingSystem::create_processes() {
	for (int i = 0; i < program_files.size(); i++) {
		process_vector.push_back(
			Process::Process(program_files[i])
		);
	}
}

void OperatingSystem::execute_processes() {
	do {
		std::vector<Process> process_queue = scheduler.schedule_processes(&process_vector);
		dispatcher.dispatch_processes(process_queue);
		for (int i = 0; i < process_queue.size(); i++) {
			if (process_queue[i].get_PCB().process_state == RUN) {
				CPU0.execute_program(process_queue[i], scheduler);
			}
		}
	} while (scheduler.processes_in_queue());

	for (int i = 0; i < process_vector.size(); i++) {
		if (process_vector[i].get_PCB().process_state != EXIT) {
			execute_processes();
		}
		else {
			std::cout << "All processes executed. Aborting.";
		}
	}
}
