#pragma once

#include "ui_OperatingSystemGUI.h"
#include <QtWidgets/QMainWindow>

class OperatingSystemGUI : public QMainWindow {
  Q_OBJECT

public:
  OperatingSystemGUI(QWidget *parent = Q_NULLPTR);

private:
  Ui::OperatingSystemGUIClass ui;
};
