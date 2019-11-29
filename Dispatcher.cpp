#include "Dispatcher.h"

std::vector<std::shared_ptr<Process>> Dispatcher::dispatch_processes(const std::vector<std::shared_ptr<Process>>& processes, Cache& cache) {
	int threads = 0;
	std::vector<std::shared_ptr<Process>> processes_out;
	cache.clear_cache();
	for (auto i = processes.begin(); i != processes.end(); ++i) {
		cache.cache_process(*i);
	}
	for (auto i = processes.rbegin(); i != processes.rend(); ++i) {
		Process& temp = *(*i);
		if (temp.get_state() == READY && threads < 4 && cache.check_cache(temp)) {
			temp.update_state(RUN);
			threads++;
			processes_out.push_back(*i);
		}
		else {
			break;
		}
	}
	return processes_out;
}
