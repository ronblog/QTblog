#include "griantwidget.h"
#include <QPainter>
#include <QMouseEvent>

GriantWidget::GriantWidget(QWidget *parent) : QWidget(parent)
{

}


void GriantWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	painter.setCompositionMode(QPainter::CompositionMode_Overlay);
//	{
//		QRadialGradient gg(QPointF(200, 200),300);
//		gg.setColorAt(0.1,Qt::red);
//		gg.setColorAt(0.2,Qt::yellow);
//		gg.setColorAt(0.4,Qt::blue);
//		gg.setColorAt(0.7,Qt::gray);
//		gg.setColorAt(1,Qt::darkCyan);
//		painter.fillRect(rect(),QBrush(gg));
//	}


//	{
//		QRadialGradient gg(QPointF(100, 100),300);
//		gg.setColorAt(0.1,Qt::red);
//		gg.setColorAt(0.2,Qt::yellow);
//		gg.setColorAt(0.4,Qt::blue);
//		gg.setColorAt(0.7,Qt::gray);
//		gg.setColorAt(1,Qt::darkCyan);
//		painter.fillRect(rect(),QBrush(gg));
//	}

//	{
//		QRadialGradient gg(QPointF(500, 500),300);
//		gg.setColorAt(0.1,Qt::red);
//		gg.setColorAt(0.2,Qt::yellow);
//		gg.setColorAt(0.4,Qt::blue);
//		gg.setColorAt(0.7,Qt::gray);
//		gg.setColorAt(1,Qt::darkCyan);
//		painter.fillRect(rect(),QBrush(gg));
//	}


	for (auto pt: lt_points)
	{
		QRadialGradient gg(pt,300);
		gg.setColorAt(0.1,Qt::red);
		gg.setColorAt(0.2,Qt::yellow);
		gg.setColorAt(0.4,Qt::blue);
		gg.setColorAt(0.7,Qt::gray);
		gg.setColorAt(1,Qt::darkCyan);
		painter.fillRect(rect(),QBrush(gg));
	}


}


void GriantWidget::mousePressEvent(QMouseEvent *event)
{
	lt_points << event->pos();
	update();

}
