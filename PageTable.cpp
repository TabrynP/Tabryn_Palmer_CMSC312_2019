#include "PageTable.h"

bool PageTable::send_pages(std::shared_ptr<Process> process, MainMemory& mem) {
	int random = randomize();
	if (random < 90) {
		page_hit(process, mem);
		return true;
	}
	else {
		page_miss(process);
		return false;
	}
} 

bool PageTable::page_hit(std::shared_ptr<Process> process, MainMemory& mem) {
	if (mem.add_page(process)) {
		process->update_state(READY);
		return true;
	}
	else {
		process->update_state(WAIT);
		return false;
	}
}
void PageTable::page_miss(std::shared_ptr<Process> process) {
	process->set_random_IO(50);
}
int PageTable::randomize() {
	srand(time(NULL));
	return rand() % 100 + 1;
}

// FIFO page-replacement taking advantage of std::vector
void PageTable::page_replace(std::shared_ptr<Process> process, MainMemory& m) {
	m.pages.erase(m.pages.begin());
	send_pages(process, m);
}
