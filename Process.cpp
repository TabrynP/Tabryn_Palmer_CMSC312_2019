#include "Process.h"

Process::Process(const std::string& program_file, std::shared_ptr<SharedMemory> mem) {
	init_process(init_program_file(program_file));
	shared_memory = mem;
	process_PCB.program_file = program_file;
}

Process::Process(const Process& old_process) {
	process_map_vector = old_process.process_map_vector;
	process_PCB = old_process.process_PCB;
	children = old_process.children;
	virtual_memory = old_process.virtual_memory;
	is_child = old_process.is_child;
	is_parent = old_process.is_parent;
	just_ran = old_process.just_ran;
	is_shortest_job = old_process.is_shortest_job;
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

std::shared_ptr<Process> Process::fork() {
	srand(time(NULL));
	int process = rand() % 4 + 1;
	std::string program_file = "Process_" + std::to_string(process) + ".txt";
	std::shared_ptr<Process> child = std::make_shared<Process>(program_file, shared_memory);
	set_child(child);
	child->is_child = true;
	is_parent = true;
	return child;
}

void Process::abort(Process& child) {
	for (auto it = children.begin(); it != children.end(); ++it) {
		Process& temp = (*(*it));
		if (temp == child) {
			temp.update_state(EXIT);
		}
	}
}

void Process::init_process(const std::vector<std::string>& program_file) {
	int total_runtime = 0;
	std::string name = "placeholder";
	State current_state = NEW;
	process_PCB.in_critical = false;
	process_PCB.in_memory = false;
	process_PCB.random_IO = 0;

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
	is_child = false;
	process_PCB.total_runtime = 0;
	for (int i = 0; i < process_map_vector.size(); i++) {
		process_PCB.total_runtime += process_map_vector[i].runtime;
	}
	is_parent = false;
	priority = 0;
	virtual_memory = VirtualMemory(process_PCB.memory);
	just_ran = false;
	is_shortest_job = false;
}

std::vector<std::string> Process::init_program_file(const std::string& file_in) {
	std::string line;
	std::ifstream program_file;
	std::vector<std::string> file_lines;
	program_file.open(file_in);
	if (program_file.is_open()) {
		while (std::getline(program_file, line)) {
			file_lines.push_back(line);
		}
	}
	return file_lines;
}