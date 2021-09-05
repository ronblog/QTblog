#include "window2.h"
#include <QPainter>
#include <QTimerEvent>
#include <random>
#include <iostream>
#include <QDebug>
#include <QPushButton>

Window2::Window2(QWidget *parent) : QMainWindow(parent)
{
	setWindowTitle("W2");
	resize(600,600);
	_init = false;
	ms = 1;
	nTotal = 5;

	{
		QPushButton* pt = new QPushButton(this);
		pt->setText("Start 1");
		pt->setGeometry(520,550,75, 22);
		connect(pt, &QPushButton::clicked, this,&Window2::on_click);
	}
	{
		QPushButton* pt = new QPushButton(this);
		pt->setText("Start 2");
		pt->setGeometry(520,520,75, 22);
		connect(pt, &QPushButton::clicked, this,&Window2::on_click);
	}

	{
		QPushButton* pt = new QPushButton(this);
		pt->setText("Start 3");
		pt->setGeometry(520,480,75, 22);
		connect(pt, &QPushButton::clicked, this,&Window2::on_click);
	}

}

void Window2::on_click()
{
	auto btn = dynamic_cast<QPushButton*>(sender());
	if (btn)
	{
		auto str = btn->text();
		if (str == "Start 1")
			_runIndex = 0;
		if (str == "Start 2")
			_runIndex = 1;
		if (str == "Start 3")
			_runIndex = 2;
	}
	for (auto s : _sharps )
		s->reStart();
	nType = 0;
	startTimer(1);
}


void Window2::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	for (auto s : _sharps )
	{
		s->draw(painter);
		//painter.setPen(QPen(s->color(),1,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin));
		//painter.drawPath(s->path());
	}

}


void Window2::timerEvent(QTimerEvent *event)
{
	//one by one;
	if (_runIndex==0) runOneByOne(event->timerId());
	else if (_runIndex==1) runByType(event->timerId());
	else if (_runIndex==2) runByGroup(event->timerId());
}

void Window2::runOneByOne(int id)
{
	qDebug() << __FUNCTION__;
	for (auto s : _sharps )
	{
		if (!s->isStarted())
		{
			s->start(ms);
			return;
		}
		else if (!s->isTimeOut())
		{
			update();
			return;
		}
	}
	{
		killTimer(id);
		qDebug() << "All Done";
	}
}

void Window2::runByType(int id)
{
	qDebug() << __FUNCTION__;
	for (auto s : _sharps )
	{
		//if (s->metaObject()->className() == "Spiral")
		if (nType==0 && dynamic_cast<Spiral*>(s) && !s->isStarted())
		{
			s->start(ms);
		}

		else if (nType==1 && dynamic_cast<Line*>(s) && !s->isStarted())
		{
			s->start(ms);

		}

		else if (nType==2 && dynamic_cast<Polygon*>(s) && !s->isStarted())
		{
			s->start(ms);

		}

		else if (nType==3 && dynamic_cast<Circle*>(s) && !s->isStarted())
		{
			s->start(ms);

		}

		else if (nType==4 && dynamic_cast<Block*>(s) && !s->isStarted())
		{
			s->start(ms);

		}

	}

	for (auto s : _sharps )
	{
		//if (s->metaObject()->className() == "Spiral")
		if (nType==0 && dynamic_cast<Spiral*>(s) &&!s->isTimeOut())
			{
				update();
				return;
			}

		else if (nType==1 && dynamic_cast<Line*>(s) && !s->isTimeOut())
			{
				update();
				return;
			}

		else if (nType==2 && dynamic_cast<Polygon*>(s) && !s->isTimeOut())
			{
				update();
				return;
			}

		else if (nType==3 && dynamic_cast<Circle*>(s) && !s->isTimeOut())
			{
				update();
				return;
			}

		else if (nType==4 && dynamic_cast<Block*>(s) && !s->isTimeOut())
			{
				update();
				return;
			}

	}

		nType++;
	if(nType > nTotal )
	{
		killTimer(id);
		qDebug() << "All Done";
		update();
	}

}

void Window2::runByGroup(int id)
{
	qDebug() << __FUNCTION__;
	for (auto s : _sharps )
	{
		if (s->groupId() == nType && !s->isStarted())
		{
			s->start(ms);
		}
	}

	for (auto s : _sharps )
	{
		if (s->groupId() == nType && !s->isTimeOut())
		{
			update();
			return;
		}
	}

	nType++;

	if(nType > nTotal)
	{
		qDebug() << "--------- Done! -------";
		killTimer(id);
	}
}



void Window2::showEvent(QShowEvent *event)
{
	if (!_init )
	{
		std::random_device rd;  //Will be used to obtain a seed for the random number engine
			//std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

		std::seed_seq seed2{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
		std::mt19937 gen(seed2);

		_init = true;

		QColor clr(214, 137, 16 );
		QPoint pt(300,300);

		for (int n=0; n<6; n++)
		{
			float x = 100 * sin(60 * n* PI/180);
			float y = 100 * cos(60 * n* PI/180);
			//qDebug() << x << y;
			QPointF pt2= QPointF(300+x, 300+y);
			Line* ln = new Line (QLine(pt,pt2.toPoint()));
			ln->setColor(Qt::red);
			_sharps<<ln;
			auto sp  = new Spiral(pt2.toPoint(),6);
			sp->setColor(Qt::blue);
			_sharps<<sp;

			std::uniform_int_distribution<> disx(0,6);
			sp->setGroupId( disx(gen));



		}

		for (int n=2; n< 5; n++)
		{
			QPolygonF py;
			int len = 100 + n* 30;
			for (int m=0; m<6; m++)
			{
				float x = len* sin(60 * m* PI/180);
				float y = len * cos(60 * m* PI/180);
				QPointF pt2= QPointF(300+x, 300+y);

				py<< pt2;
			}
			auto polygon = new Polygon(py);
			polygon->setColor(QColor(72, 201, 176));
			//polygon->setColor(Qt::darkCyan);
			_sharps << polygon;
			std::uniform_int_distribution<> disx(0,6);
			polygon->setGroupId( disx(gen));

			if (n==3)
			{
				for (auto pt2 : py)
				{
					auto cc = new Circle(pt2,30);
					_sharps << cc;
				}
				QPolygonF py11;
				py11 << py[0] << py[2] <<py[4];
				auto py1 = new Polygon(py11);
				py1->setColor(Qt::yellow);

				QPolygonF py12;
				py12 << py[1] << py[3] <<py[5];
				auto py2 = new Polygon(py12);
				py2->setColor(Qt::yellow);
				_sharps << py1 << py2;
			}
			if (n==4)
			{
				for (auto pt2 : py)
				{
					auto cc = new Block(QRect(pt2.x()-5,pt2.y()-5,10,10));
					_sharps << cc;
					cc->setColor(clr);
				}
			}
		}
		//center sqiral;
		{
			auto sp  = new Spiral(QPointF(300,300),6);
			 sp->setColor(Qt::gray);
			_sharps<<sp;
		}



	}
}
