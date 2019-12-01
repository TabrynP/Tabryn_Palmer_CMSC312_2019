#pragma once

#include <QtWidgets/QWidget>
#include <qtimer.h>
#include "ui_OperatingSystemGUI.h"
#include "OperatingSystem.h"

struct InputOptions {
	QString scheduler_type = "set_scheduler_type";
	QString new_process = "new_process";
	QString stop_process = "stop_process";
	QString new_processes = "new_processes";
};

class OperatingSystemGUI : public QWidget
{
	Q_OBJECT

public:
	OperatingSystemGUI(QWidget* parent = Q_NULLPTR);

public slots:
	void on_lineEdit_returnPressed();
	void on_timer_timeout();
private:
	Ui::OperatingSystemGUI ui;
	InputOptions options;
	QTimer* timer;
	OperatingSystem system;
	void update_process_table();
	void update_running_table();
	void update_scheduler_table();
	void parse_process_PCB(
		QString& state,
		QString& name,
		QString& runtime,
		QString& current_instruction,
		QString& sleeping,
		QString& critical,
		QString& in_memory,
		PCB& PCB
	);
	QStringList header_labels;
};
