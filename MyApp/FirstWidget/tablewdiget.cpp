#include "tablewdiget.h"
#include "ui_tablewdiget.h"
#include <QPainter>
#include <QDebug>

const int bar_min_width = 1;
const int bar_max_width = 10;

TableWdiget::TableWdiget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::TableWdiget)
{
	ui->setupUi(this);
	startTimer(1);

	lt_datas<< 9<<8<<4<<5;
	max = 9;
}

TableWdiget::~TableWdiget()
{
	delete ui;
}


void TableWdiget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	int w = width();
	int h = height();
	painter.drawRect( 5, h* 0.2,w - 10, h*0.8 - 10);
	if (lt_datas.size() ==0 || drawed_datas.size() ==0)
		return;
	int s_w = w / lt_datas.size()/2;
	int n = 0;
	int h_used = h*0.8-10;
	float h_unit = h_used/max;

	qDebug() << s_w;
	s_w = qMin(s_w,bar_max_width);
	s_w = qMax(s_w,bar_min_width);

	for (float v : drawed_datas)
	{
		QRect rt(n*s_w*2+8,h-10-v*h_unit,s_w,v*h_unit);
		painter.drawRect(rt);
		n++;
	}
}


void TableWdiget::timerEvent(QTimerEvent *event)
{
	if (drawed_datas.size() != lt_datas.size() || drawed_datas[drawed_datas.size()-1] != lt_datas[lt_datas.size()-1])
	{
		if( drawed_datas.size()==0 || drawed_datas[drawed_datas.size()-1] == lt_datas[drawed_datas.size()-1])
			drawed_datas << 0;
		else
			drawed_datas[drawed_datas.size()-1]= drawed_datas[drawed_datas.size()-1]+1;
		update();
	}
	else
		killTimer(event->timerId());
}
