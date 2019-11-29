#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "Process.h"
#include "Cache.h"

class OperatingSystem;

class Dispatcher {
public:
	std::vector<std::shared_ptr<Process>> dispatch_processes(const std::vector<std::shared_ptr<Process>>& process, Cache& c);
};

#endif //DISPATCHER_H