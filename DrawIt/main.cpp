#include "drawit.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QCoreApplication::setApplicationName("Draw It");
	DrawIt w;
	w.show();
	return a.exec();
}
