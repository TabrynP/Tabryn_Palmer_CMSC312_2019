#ifndef EXTERNAL_STORAGE_H
#define EXTERNAL_STORAGE_H

#include "Process.h"
#include <string>

class ExternalStorage {
public:
  void init_process(const std::string &program_file);
  bool is_init(const std::string &program_file);
  Process get_process(const std::string &program_file);

private:
  std::vector<Process> initialized_processes;
  std::vector<std::string> init_program_files;
};

#endif // EXTERNAL_STORAGE_H
