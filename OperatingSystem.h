// Tabryn Palmer CMSC312 Project
#ifndef OPERATING_SYSTEM_H
#define OPERATING_SYSTEM_H

#include<string>
#include<vector>
#include <fstream>
#include <iostream>
#include "Process.h"
#include "CPU.h"
#include "Scheduler.h"
#include "Dispatcher.h"
#include "SharedMemory.h"
#include "ExternalStorage.h"
#include "PageTable.h"
#include "Mailbox.h"
#include "Cache.h"
 
class OperatingSystem {
public: 
	OperatingSystem(int processes_in);

	void create_processes(std::vector<std::string> files_in);
	void execute_processes();
	void execute_one_thread(const std::vector<std::shared_ptr<Process>>& running, std::vector<std::shared_ptr<Process>>& process_queue);
	void execute_two_threads(const std::vector<std::shared_ptr<Process>>& running, std::vector<std::shared_ptr<Process>>& process_queue);
	void execute_three_threads(const std::vector<std::shared_ptr<Process>>& running, std::vector<std::shared_ptr<Process>>& process_queue);
	void execute_four_threads(const std::vector<std::shared_ptr<Process>>& running, std::vector<std::shared_ptr<Process>>& process_queue);
	void create_children();
	void prioritize_processes();
	std::vector<std::shared_ptr<Process>> update_process_states(std::vector<std::shared_ptr<Process>>& processes, Semaphore& s, MainMemory& m, PageTable& t);
	bool processes_in_queue() {
		return in_queue;
	}
	void order_by_priority(std::vector<std::shared_ptr<Process>> processes);
	std::vector<std::shared_ptr<Process>> get_ready_processes(std::vector<std::shared_ptr<Process>>& processes);
	std::shared_ptr<Mailbox> random_message_pass(std::vector<std::shared_ptr<Process>> ready_queue);

private:
	CPU CPU0;
	CPU CPU1;
	Scheduler scheduler;
	Dispatcher dispatcher;
	ExternalStorage external_storage;
	Cache cache;
	std::shared_ptr<PageTable> page_table;
	std::vector<std::shared_ptr<Process>> process_vector;
	int num_processes;
	int time_quantum;
	bool in_queue;
};

static void set_current_state(Process& process, int);
static void print_PCB(Process&);
static void move_to_back(std::vector<std::shared_ptr<Process>>& process_vector, std::vector<std::shared_ptr<Process>>::iterator& i);
static bool test_memory(std::shared_ptr<Process>, MainMemory&, PageTable& t);
static void remove_from_memory(std::shared_ptr<Process>, MainMemory&);

#endif //OPERATING_SYSTEM_H
