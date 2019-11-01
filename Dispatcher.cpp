#include "Dispatcher.h"

void Dispatcher::dispatch_processes(std::vector<std::shared_ptr<Process>> processes) {
	if (processes.back()->get_state() == READY) {
		processes.back()->update_state(RUN);
	}
}
