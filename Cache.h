#ifndef CACHE_H
#define CACHE_H

#include <memory>
#include <vector>

#include "Process.h"

class Cache {
public:
  Cache() { cpu_cache = 20; }
  bool check_cache(const Process &p) const;
  void cache_process(std::shared_ptr<Process> p);
  bool check_cache_full();
  void clear_cache() { cached_processes.clear(); }

private:
  int cpu_cache;
  // That's right more vectors of pointers this program is a goddamn memory
  // nightmare I hate my life
  std::vector<std::shared_ptr<Process>> cached_processes;
};

#endif // CACHE_H
