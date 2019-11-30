#include "VirtualMemory.h"

VirtualMemory::VirtualMemory(int memory_in) {
	// Split process memory into discrete chunks of 20 pages.
	for (int i = 0; i < memory_in; i += 20) {
		if ((memory_in - i) > 20) {
			pages.push_back(20);
		}
		else {
			pages.push_back(memory_in - i);
		}
	}
}