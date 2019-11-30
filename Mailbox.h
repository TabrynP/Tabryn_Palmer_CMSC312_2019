#ifndef MAILBOX_H
#define MALIBOX_H

#include <memory>
#include <string>
#include <vector>

#include "Process.h"
struct Mailbox {
public:
  Mailbox(std::shared_ptr<Process> p1, std::shared_ptr<Process> p2) {
    message = "message";
    processes.push_back(p1);
    processes.push_back(p2);
  }
  bool write_message(Process &process, std::string message);
  std::string read_message(Process &process);

private:
  std::string message;
  std::vector<std::shared_ptr<Process>> processes;
};

#endif // MAILBOX_H
