#pragma once
#include "ProcessTypedef.h"

namespace Process {
	class ProcessScript {
	public:
		ProcessScript() {}
		void set_runtime();
		void get_runtime();
		void execute();
		void script_type();
	private:
		int runtime;
		script script_type;
	};
}
