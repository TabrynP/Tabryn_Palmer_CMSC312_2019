// Tabryn Palmer CMSC312 Project
#include<iostream>
#include<string>
#include<vector>
#include "Process.h"
#include "PCB.h"
#include "CPU.h"
#include "Scheduler.h"
#include "Dispatcher.h"
 

class OperatingSystem {
public: 
	OperatingSystem() {}

	void read_program_file(std::string filename);

private:
	CPU CPU0;
	Scheduler scheduler;
	std::vector<PCB> pcb_vector;
	Dispatcher dispatcher;
	std::vector<Process::Process> process_vector;
};
