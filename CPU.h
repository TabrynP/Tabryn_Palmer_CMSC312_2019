// Tabryn Palmer CMSC 312 Project

#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <random>
#include <time.h>
#include <thread>
#include <chrono>

#include "Process.h"
#include "Scheduler.h"

class CPU {
public:
	CPU() {
		available_threads = 0;
	}
	void execute_program(Process& process, const Scheduler& scheduler);
private:
	int available_threads;
};

void random_IO(Process& p);

#endif //CPU_H
