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
	CPU() {
		available_threads = 0;
	}
	friend struct thread;
	void execute_program(std::shared_ptr<Process> processes, Scheduler scheduler);
private:
	int available_threads;
};

void random_IO(Process& p);

#endif //CPU_H
