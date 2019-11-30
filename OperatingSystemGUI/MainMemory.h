#ifndef MAIN_MEMORY_H
#define MAIN_MEMORY_H

#include <vector>
#include <memory>
#include "Process.h"

/******************************************************************
 Main memory class. Currently will just add up all the processes'
 total memory and decide whether or not there's room, but
 eventually it should have support for paging and frames and
 all that good stuff.
*******************************************************************/
class MainMemory {
public:
	MainMemory() {
		memory_size = 4096;
	}

	bool add_page(std::shared_ptr<Process> process);
	void delete_page(std::shared_ptr<Process> process);
	bool has_page(std::shared_ptr<Process> process);
	int used_memory();

private:
	// Processes corresponding to pages (will probably be vector of Page objects once I make that class).
	std::vector<std::shared_ptr<Process>> pages;
	// Total available memory (always 4096).
	int memory_size;

	bool mem_available(std::shared_ptr<Process> process);
};


#endif