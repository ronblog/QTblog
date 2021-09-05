#include "dbplugin.h"
#include <QWidget>
#include <QDebug>
//Q_EXPORT_PLUGIN2(plugin, myPlugin);
#include "mydbwidget.h"

DBPlugin::DBPlugin(QObject *parent)
	: QGenericPlugin(parent), MyPluginInterface(parent)
{
	setObjectName("Test");
}

QString DBPlugin::name() {return "DB-SQL";}

void DBPlugin::slot_add()
{
	qDebug() << "added";
}

QObject *DBPlugin::create(const QString &name, const QString &spec)
{
	//static_assert(false, "You need to implement this function");
	return new QObject();
}


QWidget *DBPlugin::createWidget(QWidget* parent)
{
	QWidget* w = new MyDBWidget(parent);
	return w;

}

QMenu *DBPlugin::createMenu(QWidget* parent)
{
	QMenu* menu = new QMenu(parent);
	auto rc = menu->addAction("Add");
	connect(rc, &QAction::triggered, this, &DBPlugin::slot_add);
	menu->addAction("Delete");
	return menu;
}
