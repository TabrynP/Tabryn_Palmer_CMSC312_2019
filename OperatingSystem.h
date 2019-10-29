// Tabryn Palmer CMSC312 Project
#ifndef OPERATING_SYSTEM_H
#define OPERATING_SYSTEM_H

#include<string>
#include<vector>
#include <fstream>
#include <iostream>
#include "Process.h"
#include "PCB.h"
#include "CPU.h"
#include "Scheduler.h"
#include "Dispatcher.h"
 
class OperatingSystem {
public: 
	OperatingSystem(int processes_in);

	void read_program_file(std::string filename);
	void get_num_processes();
	void create_processes();
	void execute_processes();

private:
	CPU CPU0;
	Scheduler scheduler;
	Dispatcher dispatcher;
	std::vector<Process> process_vector;
	std::vector<std::vector<std::string>> program_files;
	int num_processes;
};

#endif //OPERATING_SYSTEM_H
