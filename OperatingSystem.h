// Tabryn Palmer CMSC312 Project
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
	OperatingSystem();

	void read_program_file(std::string filename);
	void get_num_processes();
	void create_processes();
	void execute_processes();

private:
	CPU CPU0;
	Scheduler scheduler;
	std::vector<PCB> pcb_vector;
	Dispatcher dispatcher;
	std::vector<Process> process_vector;
	std::vector<std::vector<std::string>> program_files;
	int num_processes;
};
