#include "MainMemory.h"

bool MainMemory::add_page(std::shared_ptr<Process> process) {
	if (mem_available(process) && !(has_page(process))) {
		pages.push_back(process);
		process->set_in_memory(true);
		return true;
	}
	else {
		return false;
	}
}

void MainMemory::delete_page(std::shared_ptr<Process> process) {
	for (auto i = pages.begin(); i != pages.end(); i++) {
		if (process == *i) {
			auto temp = *(*i);
			temp.set_in_memory(false);
			pages.erase(i);
			break;
		}
	}
}

bool MainMemory::mem_available(std::shared_ptr<Process> process) {
	int current_mem = used_memory();
	if (current_mem + process->get_PCB().memory > memory_size) {
		return false;
	}
	else {
		return true;
	}
}

bool MainMemory::has_page(std::shared_ptr <Process> process) {
	bool has = false;
	for (auto i = pages.begin(); i != pages.end(); i++) {
		if (process == *i) {
			has = true;
			break;
		}
	}
	return has;
}

int MainMemory::used_memory() {
	int current_mem = 0;
	for (auto i = pages.begin(); i != pages.end(); i++) {
		auto& temp = **i;
		current_mem = current_mem + temp.get_PCB().memory;
	}
	return current_mem;
}
