#include "chartplugin.h"
#include <QWidget>
#include <QDebug>
//Q_EXPORT_PLUGIN2(plugin, myPlugin);
#include "imagecomposer.h"

ChartPlugin::ChartPlugin(QObject *parent)
	: QGenericPlugin(parent), MyPluginInterface(parent)
{
	setObjectName("Test");
}

QString ChartPlugin::name() {return "Image";}

void ChartPlugin::slot_add()
{
	qDebug() << "added";
}

QObject *ChartPlugin::create(const QString &name, const QString &spec)
{
	//static_assert(false, "You need to implement this function");
	return new QObject();
}


QWidget *ChartPlugin::createWidget(QWidget* parent)
{
	QWidget* w = new ImageComposer(parent);
	return w;

}

QMenu *ChartPlugin::createMenu(QWidget* parent)
{
	QMenu* menu = new QMenu(parent);
	auto rc = menu->addAction("Add");
	connect(rc, &QAction::triggered, this, &ChartPlugin::slot_add);
	menu->addAction("Delete");
	return menu;
}
