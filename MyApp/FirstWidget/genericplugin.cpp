#include "genericplugin.h"
#include <QWidget>
#include <QDebug>
//Q_EXPORT_PLUGIN2(plugin, myPlugin);
#include "tablewdiget.h"

VTKPlugin::VTKPlugin(QObject *parent)
	: QGenericPlugin(parent), MyPluginInterface(parent)
{
}

void VTKPlugin::slot_add()
{
	qDebug() << "added";
}

QObject *VTKPlugin::create(const QString &name, const QString &spec)
{
	//static_assert(false, "You need to implement this function");
	return new QObject();
}


QWidget *VTKPlugin::createWidget(QWidget* parent)
{
	QWidget* w = new TableWdiget(parent);
	return w;

}

QMenu *VTKPlugin::createMenu(QWidget* parent)
{
	QMenu* menu = new QMenu(parent);
	auto rc = menu->addAction("Add");
	connect(rc, &QAction::triggered, this, &VTKPlugin::slot_add);
	menu->addAction("Delete");
	return menu;
}


QString VTKPlugin::name()
{
	return "Table";
}
