#ifndef VIRTUAL_MEMORY_H
#define VIRTUAL_MEMORY_H

#include <vector>

class VirtualMemory {
public:
	VirtualMemory() {
		pages.push_back(1);
	}
	VirtualMemory(int memory_in);
	std::vector<int> pages;
};

#endif // VIRTUAL_MEMORY_H