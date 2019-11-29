#include "Cache.h"

void Cache::cache_process(std::shared_ptr<Process> p) {
	if (check_cache(*p)) {
		return;
	}
	else {
		cached_processes.push_back(p);
	}
}

bool Cache::check_cache(const Process& p) const {
	for (auto i = cached_processes.begin(); i != cached_processes.end(); ++i) {
		auto temp = *(*i);
		if (temp == p) {
			return true;
		}
	}
	return false;
}

bool Cache::check_cache_full() {
	if (cached_processes.size() >= cpu_cache) {
		return true;
	}
	else {
		return false;
	}
}