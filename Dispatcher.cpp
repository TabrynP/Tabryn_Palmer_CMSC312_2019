#include "Dispatcher.h"

void Dispatcher::dispatch_processes(std::vector<Process>& processes) {
	for (int i = 0; i < processes.size() - 1; i++) {
		processes[i].update_state(READY);
	}
	processes[processes.size() - 1].update_state(RUN);
}