// Tabryn Palmer CMSC 312 Project
#include <string>
#include <vector>
#include <chrono>
#include <memory>
#include "ProcessTypedef.h"
#include "ProcessScript.h"
#include "OUT.h"
#include "YIELD.h"
#include "I_0.h"
#include "CALCULATE.h"

namespace Process {
	class Process {
	public:
		Process() {}
		void update_state();
		state get_state();
		void assign_process(int num_instructions);

	private:
		state present_state;
		int total_runtime;
		int memory;
		std::string name;
		std::vector<std::shared_ptr<ProcessScript>> script_vector;
	};
}
