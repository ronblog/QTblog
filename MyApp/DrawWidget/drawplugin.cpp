#include "drawplugin.h"
#include <QWidget>
#include <QDebug>
//Q_EXPORT_PLUGIN2(plugin, myPlugin);
#include "griantwidget.h"

DrawPlugin::DrawPlugin(QObject *parent)
	: QGenericPlugin(parent), MyPluginInterface(parent)
{
	setObjectName("Test");
}

QString DrawPlugin::name() {return "Draw";}

void DrawPlugin::slot_add()
{
	qDebug() << "added";
}

QObject* DrawPlugin::create(const QString &name, const QString &spec)
{
	//static_assert(false, "You need to implement this function");
	return new QObject();
}


QWidget *DrawPlugin::createWidget(QWidget* parent)
{
	QWidget* w = new GriantWidget(parent);
	return w;

}

QMenu* DrawPlugin::createMenu(QWidget* parent)
{
	QMenu* menu = new QMenu(parent);
	auto rc = menu->addAction("Add");
	connect(rc, &QAction::triggered, this, &DrawPlugin::slot_add);
	menu->addAction("Delete");
	return menu;
}
