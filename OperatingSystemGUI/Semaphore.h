#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <vector>

#include "Process.h"

struct Semaphore {
	bool value;
	std::vector<Process&> process_queue;
};

void wait(Semaphore& s, Process& p) {
	if (s.value >= 1) {
		s.value = 0;
	}
	else {
		s.process_queue.push_back(p);
	}
}

void signal(Semaphore& s) {
	if (s.process_queue.empty()) {
		s.value = 1;
	}
	else {
		s.process_queue.pop_back();
	}
}

#endif // SEMAPHORE_H