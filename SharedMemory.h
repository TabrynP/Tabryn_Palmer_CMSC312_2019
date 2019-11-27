#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <string>

struct SharedMemory {
public:
	SharedMemory() {
		shared_int = 5;
		shared_string = "shared";
	}

	std::string access_string() {
		return shared_string;
	}

	void modify_string(std::string new_string) {
		shared_string = new_string;
	}

	int access_int() {
		return shared_int;
	}

	int modify_int(int new_int) {
		shared_int = new_int;
	}
private:
	std::string shared_string;
	int shared_int;
};

#endif // SHARED_MEMORY_H
