#include "Process.h"

namespace Process {
	class Process {
	public:
		Process() {}
		void update_state();
		state get_state();

	private:
		state present_state;

	};

	typedef enum state_t {
		NEW = 0,
		READY = 1,
		RUN = 2,
		WAIT = 3,
		EXIT = 4,
	} state;
}