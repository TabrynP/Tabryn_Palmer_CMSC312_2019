// Tabryn Palmer CMSC 312 Project

#ifndef CPU_H
#define CPU_H

#include <iostream>

#include "Process.h"
#include "Scheduler.h"

class CPU {
public: 
	void execute_program(const Process& process, const Scheduler& scheduler);
};

#endif //CPU_H
