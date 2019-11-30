#include "CPU.h"

void CPU::execute_program(Process& process, const Scheduler& scheduler, std::vector<std::shared_ptr<Process>>& process_queue) {
	PCB pcb = process.get_PCB();
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
	random_IO(process);
	random_child_spawn(process, process_queue);
	process.just_ran = true;
	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void random_IO(Process& p) {
	std::srand(std::time(NULL));
	int random = std::rand() % 10000 + 1;
	if (random >= 9000) {
		random = random / 100;
		std::cout << "Random IO Event Has Occured! Process will enter the waiting state for " << random << "cycles " << std::endl;
		p.set_random_IO(random);
		p.update_state(WAIT);
	}
}

void random_child_spawn(Process& p, std::vector<std::shared_ptr<Process>>& process_queue) {
	std::srand(std::time(NULL));
	int random = std::rand() % 10000 + 1;
	if (random >= 5500) {
		process_queue.push_back(p.fork());
	}
}
