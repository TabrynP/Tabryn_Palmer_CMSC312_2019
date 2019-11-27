#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <string>

struct SharedResource {
public:
	SharedResource() {
		shared_resource = "shared_resource";
	}
	std::string shared_resource;
};


struct SharedMemory {
public:
	SharedMemory() {
		shared_int = 5;
		shared_string = "shared";
		shared_resource = SharedResource();
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
	SharedResource shared_resource;
};

#endif // SHARED_MEMORY_H
