#include "CPU.h"

void CPU::execute_program(std::shared_ptr<Process> process, Scheduler scheduler) {
	PCB pcb = process->get_PCB();
	int time_quantum = scheduler.get_time_quantum();
	if (pcb.total_runtime < time_quantum) {
		std::cout << "running process " << pcb.name << " for " << pcb.total_runtime << " cycles" << std::endl;
		for (int i = 0; i < pcb.total_runtime; i++) {}
		std::cout << "Process running complete. " << std::endl;
	}
	else {
		std::cout << "running process " << pcb.name << " for " << time_quantum << " cycles" << std::endl;
		for (int i = 0; i < time_quantum; i++) {}
		std::cout << "Process running paused. " << (pcb.total_runtime - time_quantum) << " cycles remaining" << std::endl;
	}
}
