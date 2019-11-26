#include "Dispatcher.h"

std::vector<std::shared_ptr<Process>> Dispatcher::dispatch_processes(std::vector<std::shared_ptr<Process>> processes) {
	int threads = 0;
	std::vector<std::shared_ptr<Process>> processes_out;
	for (auto i = processes.end(); i != processes.begin(); --i) {
		Process temp = *(*i);
		if (temp.get_state() == READY && threads < 4) {
			temp.update_state(RUN);
			threads++;
			processes_out.push_back(*i);
		}
	}
	return processes_out;
}
