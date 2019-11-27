// Tabryn Palmer CMSC312 Project
#ifndef OPERATING_SYSTEM_H
#define OPERATING_SYSTEM_H

#include<string>
#include<vector>
#include <fstream>
#include <iostream>
#include "Process.h"
#include "CPU.h"
#include "Scheduler.h"
#include "Dispatcher.h"
#include "SharedMemory.h"
 
class OperatingSystem {
public: 
	OperatingSystem(int processes_in);

	void read_program_file(std::string filename);
	void create_processes();
	void execute_processes();
	void execute_one_thread(std::vector<std::shared_ptr<Process>> running);
	void execute_two_threads(std::vector<std::shared_ptr<Process>> running);
	void execute_three_threads(std::vector<std::shared_ptr<Process>> running);
	void execute_four_threads(std::vector<std::shared_ptr<Process>> running);
	void create_children();

private:
	CPU CPU0;
	CPU CPU1;
	Scheduler scheduler;
	Dispatcher dispatcher;
	std::vector<std::shared_ptr<Process>> process_vector;
	std::vector<std::vector<std::string>> program_files;
	int num_processes;
};

#endif //OPERATING_SYSTEM_H
