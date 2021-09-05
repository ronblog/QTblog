#include "testwindow.h"
#include "ui_testwindow.h"

#include <QPluginLoader>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QDir>
#include "myplugininterface.h"

TestWindow::TestWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::TestWindow)
{
	ui->setupUi(this);
	loadPlugins();
}

TestWindow::~TestWindow()
{
	delete ui;
}

void TestWindow::loadPlugins()
 {
//	 const auto staticInstances = QPluginLoader::staticInstances();
//	 for (QObject *plugin : staticInstances)
//		 populateMenus(plugin);
	QDir dir(QApplication::applicationFilePath());
#ifdef Q_OS_MACOS
	dir.cdUp();
	dir.cdUp();
	dir.cdUp();
	dir.cdUp();
#endif
	dir.cd("plugin");

	QStringList filters;
	filters << "*.dylib";
	dir.setNameFilters(filters);
	dir.setFilter(QDir::Files);
	int nIndex = 0;
	qDebug() << dir.entryInfoList().size() << dir.path();
	auto pm= menuBar()->addMenu("PlugIn");

	for (auto fi: dir.entryInfoList())
	{
		qDebug() << fi;
		QString pluginpath = fi.absoluteFilePath();
		QFile file(pluginpath);
		if (!file.exists())
		{
			QMessageBox::warning(this,tr("错误信息"),tr("找不到%1文件").arg(pluginpath));
			continue;
		}
		QPluginLoader loader(pluginpath);
		QObject *instance = loader.instance(); //
		if (instance!= nullptr)
		{
			qDebug()<<pluginpath+" is loaded";
			MyPluginInterface *avc = qobject_cast<MyPluginInterface *>(instance);
			auto w = avc->createWidget(this);
			auto menu =avc->createMenu(this);
			menu->setTitle(avc->name());
			pm->addMenu(menu);
			ui->stackedWidget->addWidget(w);
			auto action = ui->menuPlugIns->addAction(avc->name());
			action->setData(nIndex);
			connect(action, &QAction::triggered, this, &TestWindow::slot_activeWindow);

			nIndex++ ;
			QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
			item->setText(avc->name());
			ui->listWidget->addItem(item);
		}
		else
		{
			QMessageBox::information(this,"failed to load plugin",loader.errorString());
		}
		// 需要手动释放
		delete instance;
	}



}

void TestWindow::populateMenus(QObject *plugin)
{

}

void TestWindow::slot_activeWindow()
{
	QAction* action = dynamic_cast<QAction*>( sender());
	if(action)
	{
		ui->stackedWidget->setCurrentIndex( action->data().toInt());
	}
}

void TestWindow::on_listWidget_currentRowChanged(int currentRow)
{
	ui->stackedWidget->setCurrentIndex( currentRow);
}
