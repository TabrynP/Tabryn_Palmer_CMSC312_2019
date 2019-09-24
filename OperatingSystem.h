// Tabryn Palmer CMSC312 Project
#include<iostream>
#include<string>
#include<vector>

class OperatingSystem {
public: 
	OperatingSystem() {}

	void read_program_file(std::string filename);

private:
	CPU CPU0;
	Scheduler scheduler;
	std::vector<PCB> pcb_vector;
	Dispatcher dispatcher;
	Process process;
};
