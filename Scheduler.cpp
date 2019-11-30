/*
	Note that my scheduling algorithm was derived form the one
	available at the following location:
	https://www.geeksforgeeks.org/program-round-robin-scheduling-set-1/

	It's been heavily modified to be much more betterererer.
*/

#include "Scheduler.h"

static void move_to_back(std::vector<std::shared_ptr<Process>>& processes, std::vector<std::shared_ptr<Process>>::iterator& i);
	static void set_current_state(Process & process, int time_quantum);


void Scheduler::schedule_processes(std::vector<std::shared_ptr<Process>>& processes, Semaphore& s) {
	processes = check_IO(processes, s);
	switch (scheduler_type) {
	case 0:
		round_robin(processes, s);
		break;
	case 1:
		shortest_job_first(processes, s);
		break;
	default:
		round_robin(processes, s);
		break;
	}
}

std::vector<std::shared_ptr<Process>> Scheduler::check_IO(std::vector<std::shared_ptr<Process>>& processes, Semaphore& s) {
	// Handle I/O and random I/O case.
	for (auto i = processes.begin(); i != processes.end(); ++i) {
		auto& process = (*(*i));
		if (process.get_current_instruction().type == "I/O") {
			process.update_state(WAIT);
			if (process.get_current_instruction().end_critical && process.is_in_critical()) {
				process.set_critical(false);
				signal(s);
			}
			set_current_state(process, time_quantum);
			move_to_back(processes, i);
		}
		if (process.get_random_IO() > 0) {
			process.update_state(WAIT);
			int random_IO = process.get_random_IO() - time_quantum;
			if (random_IO > 0) {
				process.set_random_IO(random_IO);
			}
			else {
				process.set_random_IO(0);
			}
		}
	}

	// Cut off any WAITING processes from ready queue
	std::vector<std::shared_ptr<Process>> ready_queue;
	for (auto i = processes.begin(); i != processes.end(); ++i) {
		auto& process = (*(*i));
		if (process.get_PCB().process_state == READY) {
			ready_queue.push_back(*i);
		}
	}
	return ready_queue;
}

void Scheduler::round_robin(std::vector<std::shared_ptr<Process>>& processes, Semaphore& s) {
	// Schedule remaining ready processes.
	for (auto i = processes.begin(); i != processes.end(); ++i) {
		auto& process = (*(*i));
		if (process.just_ran) {
			set_current_state(process, time_quantum);
			process.just_ran = false;
			move_to_back(processes, i);
		}
	}
}

void Scheduler::shortest_job_first(std::vector<std::shared_ptr<Process>>& processes, Semaphore& s) {
	std::vector<std::shared_ptr<ShortestJobProcess>> temp;
	std::vector < std::shared_ptr<Process>> temp_2;
	// Initialize shortest job processes
	for (auto i = processes.begin(); i != processes.end(); ++i) {
		temp.push_back(std::make_shared<ShortestJobProcess>(*(*i)));
	}
	// Call "sort" to sort by shortest job
	std::sort(temp.begin(), temp.end());
	// Replace the original processes with the ShortestJobProcesses (I love C++)
	for (int i = 0; i < processes.size(); i++) {
		*processes[i] = *temp[i];
	}
}


void wait(Semaphore& s, std::shared_ptr<Process> p) {
	s.value--;
	bool in_queue = false;
	if (s.value < 0) {
		for (auto it = s.process_queue.begin(); it != s.process_queue.end(); ++it) {
			auto temp = *it;
			if (temp == p) {
				in_queue = true;
			}
		}
		if (!in_queue) {
			s.process_queue.push_back(p);
			p->sleep();
			p->set_critical(false);
		}
	}
	else {
		p->wakeup();
		p->set_critical(true);
	}
}

void signal(Semaphore& s) {
	s.value++;
	if (s.value <= 0) {
		s.process_queue.back()->set_critical(true);
		s.process_queue.back()->wakeup();
		s.process_queue.pop_back();
	}
}

static void move_to_back(std::vector<std::shared_ptr<Process>>& processes, std::vector<std::shared_ptr<Process>>::iterator& i) {
	std::rotate(processes.begin(), i, i + 1);
}

static void set_current_state(Process& process, int time_quantum) {
	int temp = process.get_PCB().current_instruction;
	while (time_quantum > 0) {
		if (process.process_map(temp).runtime < time_quantum && time_quantum > 0) {
			int total_runtime = process.get_total_runtime() - process.process_map(temp).runtime;
			time_quantum = time_quantum - process.process_map(temp).runtime;
			process.set_current_instruction(++temp);
			process.set_total_runtime(total_runtime);
		}
		else {
			int total_runtime = process.get_total_runtime() - time_quantum;
			ProcessMap temp_map = process.process_map(temp);
			temp_map.runtime = temp_map.runtime - time_quantum;
			process.set_process_map(temp_map, temp);
			process.set_total_runtime(total_runtime);
			time_quantum = 0;
		}
	}

}
