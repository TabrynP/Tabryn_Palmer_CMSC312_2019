// Tabryn Palmer CMSC 312 Project

#include <iostream>

#include "Process.h"
#include "Scheduler.h"

class CPU {
public: 
	void execute_program(const Process& process, const Scheduler& scheduler);
};
