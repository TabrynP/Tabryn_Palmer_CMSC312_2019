#include <vector>
#include "ProcessTypedef.h"

struct PCB {
	int num_instructions;
	std::vector<Process::script> instruction_types;
	Process::state process_state;
};
