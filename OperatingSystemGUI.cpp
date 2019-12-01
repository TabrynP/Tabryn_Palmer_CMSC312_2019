#include "OperatingSystemGUI.h"

OperatingSystemGUI::OperatingSystemGUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QStringList labels = {
		"Name",
		"State",
		"Remaining Runtime",
		"Current Instruction",
		"Sleeping?",
		"In Critical?",
		"In Memory?"
	};
	header_labels = labels;
	timer = new QTimer(this);
	system = OperatingSystem();
	QObject::connect(timer, &QTimer::timeout, this, &OperatingSystemGUI::on_timer_timeout);
	timer->start(1000);
	ui.processWidget->setColumnCount(7);
	ui.processWidget->setHorizontalHeaderLabels(header_labels);
	ui.schedulerWidget->setColumnCount(7);
	ui.schedulerWidget->setHorizontalHeaderLabels(header_labels);
	ui.runningWidget->setColumnCount(7);
	ui.runningWidget->setHorizontalHeaderLabels(header_labels);
	std::vector<std::string> startup_files;
	for (int i = 0; i < 50; i++) {
		srand(time(NULL));
		int file = rand() % 4 + 1;
		startup_files.push_back("Process_" + std::to_string(file) + ".txt");
	}
	system.create_processes(startup_files);
}

void OperatingSystemGUI::on_lineEdit_returnPressed() {
		QString entered_text = ui.lineEdit->text();
		if (entered_text.contains(options.new_process) || entered_text.contains(options.new_processes)) {
			auto temp = entered_text.split(" ");
			std::vector<std::string> processes;
			// Skip the first element, since it will be "new_process" or "new_processes"
			for (int i = 1; i < temp.length(); i++) {
				processes.push_back(temp[i].toStdString());
			}
			system.create_processes(processes);
		}
		else if (entered_text.contains(options.scheduler_type)) {
			if (entered_text.contains("round-robin")) {
				system.change_scheduler_type("round-robin");
			}
			else if (entered_text.contains("shortest-job-first")) {
				system.change_scheduler_type("shortest-job-first");
			}
		}
		else if (entered_text.contains(options.stop_process)) {
			if (entered_text.contains("Login Prompt")) {
				system.remove_processes_from_queue(" Login Prompt");
			}
			if (entered_text.contains("Command Line")) {
				system.remove_processes_from_queue(" Command Line");
			}
			if (entered_text.contains("Video Game")) {
				system.remove_processes_from_queue(" Video Game");
			}
			if (entered_text.contains("antimalware")) {
				system.remove_processes_from_queue(" antimalware");
			}
		}
		ui.lineEdit->clear();
		system.in_queue = true;
}

void OperatingSystemGUI::on_timer_timeout() {
	if (system.processes_in_queue()) {
		system.execute_processes();
		update_process_table();
		update_running_table();
		update_scheduler_table();
	}
}

void OperatingSystemGUI::update_process_table() {
	ui.processWidget->clear();
	ui.processWidget->setColumnCount(7);
	ui.processWidget->setHorizontalHeaderLabels(header_labels);
	ui.processWidget->setRowCount(system.process_vector.size());
	int i = 0;
	for (auto it = system.process_vector.begin(); it < system.process_vector.end(); ++it) {
		QString state, name, runtime, 
			current_instruction, sleeping, critical, in_memory;
		auto process = *(*it);
		auto PCB = process.get_PCB();
		parse_process_PCB(state, name, runtime, current_instruction, sleeping, critical, in_memory, PCB);
		ui.processWidget->setItem(i, 0, new QTableWidgetItem(name));
		ui.processWidget->setItem(i, 1, new QTableWidgetItem(state));
		ui.processWidget->setItem(i, 2, new QTableWidgetItem(runtime));
		ui.processWidget->setItem(i, 3, new QTableWidgetItem(current_instruction));
		ui.processWidget->setItem(i, 4, new QTableWidgetItem(sleeping));
		ui.processWidget->setItem(i, 5, new QTableWidgetItem(critical));
		ui.processWidget->setItem(i, 6, new QTableWidgetItem(in_memory));
		i++;
	}
}

void OperatingSystemGUI::update_running_table() {
	ui.runningWidget->clear();
	ui.runningWidget->setColumnCount(7);
	ui.runningWidget->setHorizontalHeaderLabels(header_labels);
	ui.runningWidget->setRowCount(system.running_process_vector.size());
	int i = 0;
	for (auto it = system.running_process_vector.begin(); it < system.running_process_vector.end(); ++it) {
		QString state, name, runtime, current_instruction, sleeping, critical, in_memory;
		auto process = *(*it);
		auto PCB = process.get_PCB();
		parse_process_PCB(state, name, runtime, current_instruction, sleeping, critical, in_memory, PCB);
		ui.runningWidget->setItem(i, 0, new QTableWidgetItem(name));
		ui.runningWidget->setItem(i, 1, new QTableWidgetItem(state));
		ui.runningWidget->setItem(i, 2, new QTableWidgetItem(runtime));
		ui.runningWidget->setItem(i, 3, new QTableWidgetItem(current_instruction));
		ui.runningWidget->setItem(i, 4, new QTableWidgetItem(sleeping));
		ui.runningWidget->setItem(i, 5, new QTableWidgetItem(critical));
		ui.runningWidget->setItem(i, 6, new QTableWidgetItem(in_memory));
		i++;
	}
}

void OperatingSystemGUI::update_scheduler_table() {
	ui.schedulerWidget->clear();
	ui.schedulerWidget->setColumnCount(7);
	ui.schedulerWidget->setHorizontalHeaderLabels(header_labels);
	ui.schedulerWidget->setRowCount(system.ready_process_vector.size());
	int i = 0;
	for (auto it = system.ready_process_vector.begin(); it < system.ready_process_vector.end(); ++it) {
		QString state, name, runtime, current_instruction, sleeping, critical, in_memory;
		auto process = *(*it);
		auto PCB = process.get_PCB();
		parse_process_PCB(state, name, runtime, current_instruction, sleeping, critical, in_memory, PCB);
		ui.schedulerWidget->setItem(i, 1, new QTableWidgetItem(name));
		ui.schedulerWidget->setItem(i, 2, new QTableWidgetItem(state));
		ui.schedulerWidget->setItem(i, 3, new QTableWidgetItem(runtime));
		ui.schedulerWidget->setItem(i, 4, new QTableWidgetItem(current_instruction));
		ui.schedulerWidget->setItem(i, 5, new QTableWidgetItem(sleeping));
		ui.schedulerWidget->setItem(i, 6, new QTableWidgetItem(critical));
		ui.schedulerWidget->setItem(i, 7, new QTableWidgetItem(in_memory));
		i++;
	}
}

void OperatingSystemGUI::parse_process_PCB(
	QString& state,
	QString& name,
	QString& runtime,
	QString& current_instruction,
	QString& sleeping,
	QString& critical,
	QString& in_memory,
	PCB& PCB 
) {
	switch (PCB.process_state) {
	case NEW:
		state = "NEW";
		break;
	case READY:
		state = "READY";
		break;
	case RUN:
		state = "RUN";
		break;
	case WAIT:
		state = "WAIT";
		break;
	case EXIT:
		state = "EXIT";
		break;
	}
	runtime = QString::fromUtf8(std::to_string(PCB.total_runtime).c_str());
	current_instruction = QString::fromUtf8(std::to_string(PCB.current_instruction).c_str());
	switch (PCB.is_sleeping) {
	case true:
		sleeping = "Yes";
		break;
	case false:
		sleeping = "No";
		break;
	}
	switch (PCB.in_critical) {
	case true:
		critical = "Yes";
		break;
	case false:
		critical = "No";
		break;
	}
	switch (PCB.in_memory) {
	case true:
		in_memory = "Yes";
	case false:
		in_memory = "No";
	}
	name = QString::fromUtf8(PCB.name.c_str());
}
