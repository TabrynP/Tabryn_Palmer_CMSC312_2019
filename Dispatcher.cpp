#include "Dispatcher.h"

void Dispatcher::dispatch_processes(std::vector<Process>& processes) {
	processes[processes.size() - 1].update_state(RUN);
}