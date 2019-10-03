#include <vector>
#include "Process.h"

class Scheduler {
public:
	Scheduler(int quantum) { time_quantum = quantum;  in_queue = true; }
	std::vector<Process> schedule_processes(std::vector<Process> *process_vector);
	bool processes_in_queue() { return in_queue; }
	int get_time_quantum() const { return time_quantum; }
private:
	int time_quantum;
	bool in_queue;
};