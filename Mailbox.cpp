#include "Mailbox.h"

bool Mailbox::write_message(Process& process, std::string message_in) {
	if (processes.size() < 1) {
		return false;
	}
	for (auto it = processes.begin(); it != processes.end(); ++it) {
		auto temp = *(*it);
		if (temp == process) {
			message = message_in;
			return true;
		}
	}
	return false;
}

std::string Mailbox::read_message(Process& process) {
	if (processes.size() < 1) {
		return "ERROR";
	}
	for (auto it = processes.begin(); it != processes.end(); ++it) {
		auto temp = *(*it);
		if (temp == process) {
			return message;
		}
		else {
			return "ERROR";
		}
	}
}