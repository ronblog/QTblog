#include "audioplugin.h"
#include <QWidget>
#include <QDebug>
//Q_EXPORT_PLUGIN2(plugin, myPlugin);
#include "audiowidget.h"

AudioPlugin::AudioPlugin(QObject *parent)
	: QGenericPlugin(parent), MyPluginInterface(parent)
{
	setObjectName("Test");
}

QString AudioPlugin::name() {return "Audio";}

void AudioPlugin::slot_add()
{
	qDebug() << "added";
}

QObject *AudioPlugin::create(const QString &name, const QString &spec)
{
	//static_assert(false, "You need to implement this function");
	return new QObject();
}


QWidget *AudioPlugin::createWidget(QWidget* parent)
{
	QWidget* w = new AudioWidget(parent);
	return w;

}

QMenu *AudioPlugin::createMenu(QWidget* parent)
{
	QMenu* menu = new QMenu(parent);
	auto rc = menu->addAction("Add");
	connect(rc, &QAction::triggered, this, &AudioPlugin::slot_add);
	menu->addAction("Delete");
	return menu;
}
