
#include "ProcessScript.h"

namespace Process {
	class I_O : public ProcessScript {
	public:
		I_O() { ProcessScript(); }
		void pause_process();
	};
}
