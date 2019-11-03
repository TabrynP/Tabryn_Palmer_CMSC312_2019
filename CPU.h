// Tabryn Palmer CMSC 312 Project

#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <random>
#include <time.h>
#include <thread>
#include <chrono>
#include "PCB.h"

#include "Process.h"
#include "Scheduler.h"

class CPU {
public: 
	void execute_program(std::shared_ptr<Process> process, Scheduler scheduler);
	void random_IO(Process& p);
};

#endif //CPU_H
