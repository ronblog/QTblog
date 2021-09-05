#ifndef MYPLUGININTERFACE_H
#define MYPLUGININTERFACE_H

#include <QRect>
#include <QObject>
#include <QtPlugin>
#include <QStringList>
#include <QPainterPath>
#include <QImage>
#include <QWidget>
#include <QMenu>


class MyPluginInterface
{

public:
	MyPluginInterface(QObject* parent= nullptr);

	virtual QWidget* createWidget(QWidget* parent= nullptr) = 0;
	virtual QMenu* createMenu(QWidget* parent= nullptr) = 0;
	virtual QString name() {return "plugin";}
};

Q_DECLARE_INTERFACE(MyPluginInterface,"ronronrong");



#endif // MYPLUGININTERFACE_H
