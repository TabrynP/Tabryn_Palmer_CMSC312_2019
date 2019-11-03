#include "Process.h"

Process::Process(const std::vector<std::string>& program_file) {
	int total_runtime = 0;
	std::string name = "placeholder";
	State current_state = NEW;
	process_PCB.in_critical = false;
	process_PCB.in_memory = false;

	for (int i = 0; i < program_file.size(); i++) {
		if (program_file[i].find("Name: ") != std::string::npos) {
			std::size_t pos = program_file[i].size();
			std::size_t pos_2 = program_file[i].find(" ");
			std::size_t pos_3 = pos - pos_2;
			name = program_file[i].substr(pos_2);
		}
		else if (program_file[i].find("Total Runtime: ") != std::string::npos) {
			total_runtime = parse_number(program_file[i]);
		}
		else if (program_file[i].find("Memory: ") != std::string::npos) {
			process_PCB.memory = parse_number(program_file[i]);
		}
		else if (
			program_file[i].find("CALCULATE") != std::string::npos ||
			program_file[i].find("YIELD") != std::string::npos ||
			program_file[i].find("OUT") != std::string::npos
		) {
			bool is_critical = false;
			bool end_critical = false;
			if (program_file[i - 1] == "CRITICAL_in") {
				is_critical = true;
				end_critical = false;
			}
			else if (program_file[i - 1] == "CRITICAL_out") {
				end_critical = true;
				is_critical = false;
			}
			int map_int = parse_number(program_file[i]);
			std::size_t pos = program_file[i].find(" ");
			std::string map_string = program_file[i].substr(0, pos);
			process_map_vector.push_back(ProcessMap(map_string, map_int, is_critical, end_critical));
		}
		else if (program_file[i].find("I/O") != std::string::npos) {
			bool end_critical = false;
			int seed = parse_number(program_file[i]);
			std::size_t pos = program_file[i].find(" ");
			std::string map_string = program_file[i].substr(0, pos);
			srand((unsigned int)(time)(NULL));
			int map_int = rand() % (seed * 10);
			if (program_file[i - 1] == "CRITICAL_out") {
				end_critical = true;
			}
			else {
				end_critical = false;
			}
			process_map_vector.push_back(ProcessMap(map_string, map_int, false, end_critical));
		}
		else {
			continue;
		}
	}
	process_PCB.process_state = current_state;
	process_PCB.total_runtime = total_runtime;
	process_PCB.name = name;
	process_PCB.current_instruction = 0;
	process_PCB.is_sleeping = false;

	process_PCB.total_runtime = 0;
	for (int i = 0; i < process_map_vector.size(); i++) {
		process_PCB.total_runtime += process_map_vector[i].runtime;
	}
}

void Process::update_state(State new_state) {
	process_PCB.process_state = new_state;
}

static int parse_number(std::string program_line) {
	std::size_t pos;
	if (program_line.find(":") != std::string::npos) {
		pos = program_line.find(": ") + 2;
	}
	else {
		pos = program_line.find(" ");
	}
	std::string temp_str = program_line.substr(pos);
	std::stringstream temp_strstream(temp_str);
	int output;
	temp_strstream >> output;
	return output;
}



