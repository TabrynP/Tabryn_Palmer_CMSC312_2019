#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "Process.h"

class Dispatcher {
public:
	void dispatch_processes(std::vector<std::shared_ptr<Process>> process);
};

#endif //DISPATCHER_H