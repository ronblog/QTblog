#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class TestWindow; }
QT_END_NAMESPACE

class TestWindow : public QMainWindow
{
	Q_OBJECT

public:
	TestWindow(QWidget *parent = nullptr);
	~TestWindow();

	void loadPlugins();
	void populateMenus(QObject *plugin);

public slots:
	void slot_activeWindow();

private slots:
	void on_listWidget_currentRowChanged(int currentRow);

private:
	Ui::TestWindow *ui;
};
#endif // TESTWINDOW_H
