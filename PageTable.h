#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include "MainMemory.h"
#include "Process.h"

class PageTable {
public:
  bool send_pages(std::shared_ptr<Process> process, MainMemory &mem);
  void PageTable::page_replace(std::shared_ptr<Process> process, MainMemory& m);

private:
  bool page_hit(std::shared_ptr<Process> process, MainMemory &mem);
  void page_miss(std::shared_ptr<Process> process);
  int randomize();
};

#endif // PAGE_TABLE_H
