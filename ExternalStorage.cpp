#include "ExternalStorage.h"

void ExternalStorage::init_process(const std::string& program_file) {
	initialized_processes.push_back(Process(program_file));
	init_program_files.push_back(program_file);
}

bool ExternalStorage::is_init(const std::string& program_file) {
	for (auto it = init_program_files.begin(); it != init_program_files.end(); ++it) {
		if (*it == program_file) {
			return true;
		}
	}
	return false;
}

Process ExternalStorage::get_process(const std::string& program_file) {
	for (auto it = initialized_processes.begin(); it != initialized_processes.end(); ++it) {
		auto temp = *it;
		if (temp.get_PCB().program_file == program_file) {
			return temp;
		}
	}
	return Process(program_file);
}