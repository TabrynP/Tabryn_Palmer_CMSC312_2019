#include <iostream>
#include <string>
#include <sstream>

#include "Process.h"
#include "Dispatcher.h"
#include "OperatingSystem.h"
#include "PCB.h"
#include "CPU.h"
#include "Scheduler.h"

int main(void) {
	std::vector<std::string> program_files;
	int num_programs = 5; //default
	int program = 1;
	for (int i = 0; i < num_programs; i++) {
		std::string tempstring = std::to_string(program);
		std::string process_string = "Process_";
		process_string.append(tempstring);
		process_string.append(".txt");
		program_files.push_back(process_string);
		program++;
		if (program > 4) {
			program = 1;
		}
	}
	OperatingSystem main_system(num_programs);
	main_system.create_processes(program_files);
	main_system.execute_processes();
}
