#include "Process.h"

Process::Process(std::vector<std::string> program_file) {
	memory = 0;
	int total_runtime = 0;
	std::string name = "placeholder";
	State current_state = NEW;

	for (int i = 0; i < program_file.size(); i++) {
		if (program_file[i].find("Name:")) {
			std::size_t pos = program_file[i].size() - program_file[i].find("Name: ");
			name = program_file[i].substr(pos);
		}
		else if (program_file[i].find("Total runtime: ")) {
			total_runtime = parse_number(program_file[i]);
		}
		else if (program_file[i].find("Memory: ")) {
			memory = parse_number(program_file[i]);
		}
		else if (
			program_file[i].find("CALCULATE") ||
			program_file[i].find("YIELD") ||
			program_file[i].find("OUT")
		) {
			int map_int = parse_number(program_file[i]);
			std::size_t pos = program_file[i].find(" ");
			std::string map_string = program_file[i].substr(pos);
			process_map_vector.push_back(ProcessMap(map_string, map_int));
		}
		else if (program_file[i].find("I/O")) {
			int seed = parse_number(program_file[i]);
			std::size_t pos = program_file[i].find(" ");
			std::string map_string = program_file[i].substr(pos);
			srand(time(NULL));
			int map_int = rand() % (seed * 10);
			process_map_vector.push_back(ProcessMap(map_string, map_int));
		}
		else {
			break;
		}
	}
	process_PCB.process_state = current_state;
	process_PCB.total_runtime = total_runtime;
	process_PCB.name = name;
}

void Process::update_state(State new_state) {
	process_PCB.process_state = new_state;
}

static int parse_number(std::string program_line) {
	std::size_t pos;
	if (program_line.find(": ")) {
		pos = program_line.size() - program_line.find(": ");
	}
	else {
		pos = program_line.size() - program_line.find(" ");
	}
	std::string temp_str = program_line.substr(pos);
	std::stringstream temp_strstream(temp_str);
	int output;
	temp_strstream >> output;
	return output;
}



