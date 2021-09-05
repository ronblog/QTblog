#include "statuswidget.h"
#include <QPainter>

StatusWidget::StatusWidget(QWidget* parent)
	:QWidget(parent)
{
	status =true;
}


void StatusWidget::timerEvent(QTimerEvent *event)
{
}

void StatusWidget::mousePressEvent(QMouseEvent *event)
{
	status = !status;
	update();
}

void StatusWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	//painter.drawRoundedRect(rect(),20,20);
	QPainterPath path;
	path.addRoundedRect(rect(),20,20);

	if (status)
	{
		QPainterPath pathCircle;
		pathCircle.addEllipse(QPoint(width()/4,height()/2),height()/2,height()/2);
		painter.fillPath(path,Qt::green);
		painter.fillPath(pathCircle,Qt::white);
	}
	else
	{
		QPainterPath pathCircle;
		pathCircle.addEllipse(QPoint(width()/4*3,height()/2),height()/2,height()/2);
		painter.fillPath(path,Qt::gray);
		painter.fillPath(pathCircle,Qt::white);
	}

	//painter.setPen(Qt::white);

}
