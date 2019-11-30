#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OperatingSystemGUI.h"

class OperatingSystemGUI : public QMainWindow
{
	Q_OBJECT

public:
	OperatingSystemGUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::OperatingSystemGUIClass ui;
};
