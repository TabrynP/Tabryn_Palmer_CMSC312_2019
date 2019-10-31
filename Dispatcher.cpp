#include "Dispatcher.h"

void Dispatcher::dispatch_processes(std::vector<std::shared_ptr<Process>> processes) {
	for (int i = 0; i < processes.size(); i++) {
		if (processes[i]->get_PCB().process_state == READY) {
			processes[i]->update_state(RUN);
		}
	}
}