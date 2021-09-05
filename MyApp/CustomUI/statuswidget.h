#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H
#include <QWidget>

class StatusWidget :public QWidget
{
public:
	StatusWidget(QWidget* parent = nullptr);

	// QObject interface
protected:
	virtual void timerEvent(QTimerEvent *event);

	virtual void mousePressEvent(QMouseEvent *event);
	virtual void paintEvent(QPaintEvent *event);

	bool status;
};

#endif // STATUSWIDGET_H
