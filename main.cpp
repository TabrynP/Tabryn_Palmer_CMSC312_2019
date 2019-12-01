#include "OperatingSystemGUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	OperatingSystem s;
	QApplication a(argc, argv);
	OperatingSystemGUI w;
	w.show();
	return a.exec();
}
