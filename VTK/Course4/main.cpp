#include "mainwindow.h"

#include <QApplication>
#include <vtkQImageToImageSource.h>
#include <vtkSmartPointer.h>
#include <QLabel>
#include <QVTKOpenGLNativeWidget.h>
int main(int argc, char *argv[])
{
	QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
