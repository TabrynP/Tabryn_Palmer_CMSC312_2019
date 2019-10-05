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
	int num_programs = 0;
	std::cout << "Enter the amount of programs to run: ";
	std::cin >> num_programs;
	std::cout << "Enter the programs you want to run ( 1 - 4 ) one at a time: ";
	for (int i = 0; i < num_programs; i++) {
		std::string tempstring;
		std::getline(std::cin, tempstring);
		std::string process_string = "Process_";
		process_string.append(tempstring);
		process_string.append(".txt");
		program_files.push_back(process_string);
	}
	OperatingSystem main_system(num_programs);
	for (int i = 0; i < num_programs; i++) {
		main_system.read_program_file(program_files[i]);
	}
	main_system.execute_processes();
}