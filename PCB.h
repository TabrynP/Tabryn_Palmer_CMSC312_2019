#include <vector>
#include <string>

struct PCB {
	State process_state;
	int total_runtime;
	std::string name;
};

typedef enum State { NEW, READY, RUN, WAIT, EXIT };

