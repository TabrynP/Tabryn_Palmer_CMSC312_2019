#pragma once

#include "ProcessScript.h"

namespace Process {
	class I_O : public ProcessScript {
	public:
		I_O() { ProcessScript(); }
	private:
		int random_runtime;
		void calc_random_runtime();
		void execute_impl();
	};
}
