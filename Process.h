// Tabryn Palmer CMSC 312 Project
#include <string>
#include <vector>
#include "ProcessTypedef.h"

namespace Process {
	class Process {
	public:
		Process() {}
		void update_state();
		state get_state();

	private:
		state present_state;
		int total_runtime;
		int memory;
		std::string name;
		std::vector<CALCULATE> calculates;
		std::vector<I_0> IO;
		
	};

}
