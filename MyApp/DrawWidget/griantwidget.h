#ifndef GRIANTWIDGET_H
#define GRIANTWIDGET_H

#include <QWidget>

class GriantWidget : public QWidget
{
	Q_OBJECT
public:
	explicit GriantWidget(QWidget *parent = nullptr);

signals:

public slots:

	// QWidget interface
protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	QList<QPoint> lt_points;

};

#endif // GRIANTWIDGET_H
